//---------------------------------------------------------------------
// Implementation objects for the LabVIEW implementation of the
// gRPC MeasurementService
//---------------------------------------------------------------------
#pragma once

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <measurement_service.grpc.pb.h>
#include <condition_variable>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using namespace measurementservice;
using namespace std;

#ifdef _WIN32
    #define LIBRARY_EXPORT extern "C" __declspec(dllexport)
#else
    #define LIBRARY_EXPORT extern "C"
#endif

//---------------------------------------------------------------------
// LabVIEW definitions
//---------------------------------------------------------------------
typedef int32_t MagicCookie;
typedef MagicCookie LVRefNum;
typedef MagicCookie LVUserEventRef;

typedef struct {
	int32_t cnt; /* number of bytes that follow */
	char str[1]; /* cnt bytes */
} LStr, * LStrPtr, ** LStrHandle;


typedef struct {
	int32_t cnt; /* number of bytes that follow */
    int32_t padding;
	int8_t str[1]; /* cnt bytes */
} LV1DArray, * LV1DArrayPtr, ** LV1DArrayHandle;

//---------------------------------------------------------------------
// LabVIEW definitions
//---------------------------------------------------------------------
typedef void* LVgRPCid;
typedef void* LVgRPCServerid;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class EventData
{
public:
    EventData(ServerContext* context);

private:
	mutex lockMutex;
	condition_variable lock;

public:
	ServerContext* context;

public:
    void WaitForComplete();
    void NotifyComplete();
};

class LabVIEWMeasurementServerInstance;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class LabVIEWMeasurementServer final : public measurementservice::MeasurementService::Service
{
public:
    LabVIEWMeasurementServer(LabVIEWMeasurementServerInstance* instance);
    void SopServer();
    void RegisterEvent(string eventName, LVUserEventRef reference);

    // Overrides
    Status Invoke(ServerContext* context, const InvokeRequest* request, InvokeResponse* response) override;
    Status Query(ServerContext* context, const QueryRequest* request, QueryResponse* response) override; 
    Status Register(ServerContext* context, const RegistrationRequest* request, ServerWriter<ServerEvent>* writer) override;
    Status PerformFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, FourProbeData* response) override;
    Status StreamFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, ServerWriter<FourProbeRaw>* writer) override;

private:
    LabVIEWMeasurementServerInstance* m_Instance;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class ServerStartEventData : public EventData
{
public:
    ServerStartEventData();

public:
    int serverStartStatus;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class FourProbeMeasurementData : public EventData
{
public:
    FourProbeMeasurementData(ServerContext* context, const FourProbeRequest* request, ServerWriter<FourProbeRaw>* writer);
    FourProbeMeasurementData(ServerContext* context, const FourProbeRequest* request, FourProbeData* response);

public:
	const FourProbeRequest* request;
	grpc::ServerWriter<FourProbeRaw>* writer;
	FourProbeData* response;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class InvokeData : public EventData
{
public:
    InvokeData(ServerContext* context, const InvokeRequest* request, InvokeResponse* response);

public:
	const InvokeRequest* request;
	InvokeResponse* response;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class QueryData : public EventData
{
public:
    QueryData(ServerContext* context, const QueryRequest* request, QueryResponse* response);

public:
	const QueryRequest* request;
	QueryResponse* response;
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
class RegistrationRequestData : public EventData
{
public:
    RegistrationRequestData(ServerContext* context, const RegistrationRequest* request, ServerWriter<measurementservice::ServerEvent>* writer);

public:
    const measurementservice::RegistrationRequest* request;
    grpc::ServerWriter<measurementservice::ServerEvent>* eventWriter;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class LabVIEWMeasurementServerInstance
{
public:
    int Run(string address, string serverCertificatePath, string serverKeyPath);
    void StopServer();
    void RegisterEvent(string eventName, LVUserEventRef reference);
    void SendEvent(string name, EventData* data);

private:
    unique_ptr<Server> m_Server;
    map<string, LVUserEventRef> m_RegisteredServerMethods;

private:
    static void RunServer(string address, string serverCertificatePath, string serverKeyPath, LabVIEWMeasurementServerInstance* instance, ServerStartEventData* serverStarted);
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVErrorOutData
{
  int errCode;
  LStrHandle errMessage;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVFourProbeRawData
{
  float posVoltage;
  float posCurrent;
  float negVoltage;
  float negCurrent;
  float impedance;
  LVErrorOutData error;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVFourProbeResponse
{
    LV1DArrayHandle results;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVInvokeRequest
{
    LStrHandle command;
    LStrHandle parameter;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVInvokeResponse
{
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVQueryRequest
{
    LStrHandle query;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVQueryResponse
{
    LStrHandle message;
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVRegistrationRequest
{
    LStrHandle eventName;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVServerEvent
{
    LStrHandle eventData;
    int32_t serverId;
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void OccurServerEvent(LVUserEventRef event, EventData* data);
