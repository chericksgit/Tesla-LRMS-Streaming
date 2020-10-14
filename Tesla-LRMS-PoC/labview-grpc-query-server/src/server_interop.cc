//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <measurement_server.h>
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <mutex>
#include <thread>

#ifndef _WIN32
#include <dlfcn.h>
#endif

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using namespace std;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
typedef int (*NumericArrayResize_T)(int32_t, int32_t, void* handle, size_t size);
typedef int (*PostLVUserEvent_T)(LVUserEventRef ref, void *data);

//---------------------------------------------------------------------
//---------------------------------------------------------------------
static NumericArrayResize_T NumericArrayResize;
static PostLVUserEvent_T PostLVUserEvent;

#ifdef _WIN32

//---------------------------------------------------------------------
//---------------------------------------------------------------------
static void InitCallbacks()
{
	if (NumericArrayResize != NULL)
	{
		return;
	}

	auto lvModule = GetModuleHandle("LabVIEW.exe");
	if (lvModule == NULL)
	{
		lvModule = GetModuleHandle("lvffrt.dll");
	}
	if (lvModule == NULL)
	{
		lvModule = GetModuleHandle("lvrt.dll");
	}
	NumericArrayResize = (NumericArrayResize_T)GetProcAddress(lvModule, "NumericArrayResize");
	PostLVUserEvent = (PostLVUserEvent_T)GetProcAddress(lvModule, "PostLVUserEvent");
}

#else

//---------------------------------------------------------------------
//---------------------------------------------------------------------
static void InitCallbacks()
{
	if (NumericArrayResize != NULL)
	{
		return;
	}

	auto lvModule = dlopen("labview", RTLD_NOLOAD);
	if (lvModule == NULL)
	{
		lvModule = dlopen("liblvrt.so", RTLD_NOW);
	}
	NumericArrayResize = (NumericArrayResize_T)dlsym(lvModule, "NumericArrayResize");
	PostLVUserEvent = (PostLVUserEvent_T)dlsym(lvModule, "PostLVUserEvent");
}

#endif

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void OccurServerEvent(LVUserEventRef event, EventData* data)
{
	auto error = PostLVUserEvent(event, &data);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void SetLVString(LStrHandle* lvString, string str)
{
    auto length = str.length();    
	auto error = NumericArrayResize(0x01, 1, lvString, length);
	memcpy((**lvString)->str, str.c_str(), length);
	(**lvString)->cnt = (int)length;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string GetLVString(LStrHandle lvString)
{    
    if (lvString == NULL || *lvString == NULL)
    {
        return string();
    }

	auto count = (*lvString)->cnt;
	auto chars = (*lvString)->str;

	string result(chars, count);
    return result;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t LVCreateServer(LVgRPCServerid* id)
{
	InitCallbacks();
	auto server = new LabVIEWMeasurementServerInstance();
	*id = server;   
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t LVStartServer(char* address, char* serverCertificatePath, char* serverKeyPath, LVgRPCServerid* id)
{   
	LabVIEWMeasurementServerInstance* server = *(LabVIEWMeasurementServerInstance**)id;
	return server->Run(address, serverCertificatePath, serverKeyPath);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t LVStopServer(LVgRPCServerid* id)
{
	LabVIEWMeasurementServerInstance* server = *(LabVIEWMeasurementServerInstance**)id;
	server->StopServer();
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t RegisterServerEvent(const char* name, LVUserEventRef* item, LVgRPCServerid* id)
{
	LabVIEWMeasurementServerInstance* server = *(LabVIEWMeasurementServerInstance**)id;
	server->RegisterEvent(name, *item);
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t FourProbeMeasurementSetResponse(LVgRPCid id, LVFourProbeResponse* response)
{
	FourProbeMeasurementData* data = *(FourProbeMeasurementData**)id;
	LVFourProbeRawData* lvData = (LVFourProbeRawData*)((*response->results)->str);
	for (int x=0; x < (*response->results)->cnt; ++x)
	{
		auto rawData = data->response->add_data();
		rawData->set_posvoltage(lvData->posVoltage);
		rawData->set_poscurrent(lvData->posCurrent);
		rawData->set_negvoltage(lvData->negVoltage);
		rawData->set_negcurrent(lvData->negCurrent);
		rawData->set_impedance(lvData->impedance);
		rawData->mutable_error()->set_errcode(lvData->error.errCode);
		rawData->mutable_error()->set_errmessage(GetLVString(lvData->error.errMessage));
		lvData += 1;
	}
	data->NotifyComplete();
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t FourProbeMeasurementSetStreamResponse(LVgRPCid id, LVFourProbeRawData* response)
{
	FourProbeMeasurementData* measurementData = *(FourProbeMeasurementData**)id;

	measurementservice::FourProbeRaw data;
	data.set_posvoltage(response->posVoltage);
	data.set_poscurrent(response->posCurrent);
	data.set_negvoltage(response->negVoltage);
	data.set_negcurrent(response->negCurrent);
	data.set_impedance(response->impedance);
	data.mutable_error()->set_errcode(response->error.errCode);
	data.mutable_error()->set_errmessage(GetLVString(response->error.errMessage));

	measurementData->writer->Write(data);
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t FourProbeMeasurementComplete(LVgRPCid id)
{
	FourProbeMeasurementData* measurementData = *(FourProbeMeasurementData**)id;
	measurementData->NotifyComplete();
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t InvokeGetRequest(LVgRPCid id, LVInvokeRequest* request)
{
	InvokeData* data = *(InvokeData**)id;
    SetLVString(&request->command, data->request->command());
    SetLVString(&request->parameter, data->request->parameter());
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t InvokeSetResponse(LVgRPCid id, LVInvokeResponse* response)
{
	InvokeData* data = *(InvokeData**)id;
    data->response->set_status(response->status);
    data->NotifyComplete();
	return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t QueryGetRequest(LVgRPCid id, LVQueryRequest* request)
{
	QueryData* data = *(QueryData**)id;
    SetLVString(&request->query, data->request->query());
    return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t QuerySetResponse(LVgRPCid id, LVQueryResponse* response)
{
	QueryData* data = *(QueryData**)id;
    data->response->set_message(GetLVString(response->message));
    data->response->set_status(response->status);
    data->NotifyComplete();
    return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t RegisterGetRequest(LVgRPCid id, LVRegistrationRequest* request)
{
	RegistrationRequestData* data = *(RegistrationRequestData**)id;
    SetLVString(&request->eventName, data->request->eventname());
    return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t NotifyServerEvent(LVgRPCid id, LVServerEvent* event)
{
	RegistrationRequestData* data = *(RegistrationRequestData**)id;
    measurementservice::ServerEvent e;
    e.set_eventdata(GetLVString(event->eventData));
    e.set_serverid(event->serverId);
    e.set_status(event->status);
    data->eventWriter->Write(e);
    return 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LIBRARY_EXPORT int32_t CloseServerEvent(LVgRPCid id)
{
	RegistrationRequestData* data = *(RegistrationRequestData**)id;
    data->NotifyComplete();
    return 0;
}
