//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <measurement_service.grpc.pb.h>
#include <sstream>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;
using namespace measurementservice;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class QueryClient
{
public:
    QueryClient(shared_ptr<Channel> channel);

public:
    void Invoke(const string& command, const string& parameters);
    string Query(const string &command);
    unique_ptr<grpc::ClientReader<ServerEvent>> Register(const string& eventName);

public:
    ClientContext m_context;
    unique_ptr<MeasurementService::Stub> m_Stub;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
QueryClient::QueryClient(shared_ptr<Channel> channel)
    : m_Stub(MeasurementService::NewStub(channel))
{        
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void QueryClient::Invoke(const string& command, const string& parameters)
{
    InvokeRequest request;
    request.set_command(command);
    request.set_parameter(parameters);

    ClientContext context;
    InvokeResponse reply;
    Status status = m_Stub->Invoke(&context, request, &reply);
    if (!status.ok())
    {
        cout << status.error_code() << ": " << status.error_message() << endl;
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string QueryClient::Query(const string &command)
{
    QueryRequest request;
    request.set_query(command);
    QueryResponse reply;
    ClientContext context;

    Status status = m_Stub->Query(&context, request, &reply);

    if (status.ok())
    {
        return reply.message();
    }
    else
    {
        cout << status.error_code() << ": " << status.error_message() << endl;
        return "RPC failed";
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
unique_ptr<grpc::ClientReader<ServerEvent>> QueryClient::Register(const string& eventName)
{
    RegistrationRequest request;
    request.set_eventname(eventName);

    return m_Stub->Register(&m_context, request);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string GetServerAddress(int argc, char** argv)
{
    string target_str;
    string arg_str("--target");
    if (argc > 1)
    {
        string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != string::npos)
        {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=')
            {
                target_str = arg_val.substr(start_pos + 1);
            }
            else
            {
                cout << "The only correct argument syntax is --target=" << endl;
                return 0;
            }
        }
        else
        {
            cout << "The only acceptable argument is --target=" << endl;
            return 0;
        }
    }
    else
    {
        target_str = "localhost:50051";
    }
    return target_str;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string GetCertPath(int argc, char** argv)
{
    string cert_str;
    string arg_str("--cert");
    if (argc > 2)
    {
        string arg_val = argv[2];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != string::npos)
        {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=')
            {
                cert_str = arg_val.substr(start_pos + 1);
            }
            else
            {
                cout << "The only correct argument syntax is --cert=" << endl;
                return 0;
            }
        }
        else
        {
            cout << "The only acceptable argument is --cert=" << endl;
            return 0;
        }
    }
    return cert_str;
}

std::string read_keycert( const std::string& filename)
{	
	std::string data;
	std::ifstream file(filename.c_str(), std::ios::in);
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		data = ss.str();
	}
	return data;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
    auto target_str = GetServerAddress(argc, argv);
    auto certificatePath = GetCertPath(argc, argv);

    shared_ptr<grpc::ChannelCredentials> creds;
    if (!certificatePath.empty())
    {
        std::string cacert = read_keycert(certificatePath);
        grpc::SslCredentialsOptions ssl_opts;
        ssl_opts.pem_root_certs=cacert;
        creds = grpc::SslCredentials(ssl_opts);
    }
    else
    {
        creds = grpc::InsecureChannelCredentials();
    }
    auto channel = grpc::CreateChannel(target_str, creds);
    QueryClient client(channel);

    auto result = client.Query("Uptime");
    cout << "Server uptime: " << result << endl;

    result = client.Query("SETCONF=SMUResourceName[[CONFPARAM]]=SMU");
    cout << "Sent: SETCONF=SMUResourceName[[CONFPARAM]]=SMU, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUChannels[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=SMUChannels[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSourceMode_Sequence[[CONFPARAM]]=1021");
    cout << "Sent: SETCONF=SMUSourceMode_Sequence[[CONFPARAM]]=1021, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUOutputFunction_DCCurrent[[CONFPARAM]]=1007");
    cout << "Sent: SETCONF=SMUOutputFunction_DCCurrent[[CONFPARAM]]=1007, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSourceTransientResponse_Fast[[CONFPARAM]]=1039");
    cout << "Sent: SETCONF=SMUSourceTransientResponse_Fast[[CONFPARAM]]=1039, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUCurrent[[CONFPARAM]]=1.0");
    cout << "Sent: SETCONF=SMUCurrent[[CONFPARAM]]=1.0, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUCurrentLevelRange[[CONFPARAM]]=1.0");
    cout << "Sent: SETCONF=SMUCurrentLevelRange[[CONFPARAM]]=1.0, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUMeasurementSense_Local[[CONFPARAM]]=1008");
    cout << "Sent: SETCONF=SMUMeasurementSense_Local[[CONFPARAM]]=1008, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUMeasurementApertureTime[[CONFPARAM]]=0.010");
    cout << "Sent: SETCONF=SMUMeasurementApertureTime[[CONFPARAM]]=0.010, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSourceAdvancedSourceDelay[[CONFPARAM]]=0.000100");
    cout << "Sent: SETCONF=SMUSourceAdvancedSourceDelay[[CONFPARAM]]=0.000100, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUVoltage[[CONFPARAM]]=6");
    cout << "Sent: SETCONF=SMUVoltage[[CONFPARAM]]=6, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSourceAdvancedSequenceLoopCount[[CONFPARAM]]=571");
    cout << "Sent: SETCONF=SMUSourceAdvancedSequenceLoopCount[[CONFPARAM]]=571, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUMeasurementAdvancedDCNoiseRejection_Normal[[CONFPARAM]]=1044");
    cout << "Sent: SETCONF=SMUMeasurementAdvancedDCNoiseRejection_Normal[[CONFPARAM]]=1044, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSequenceName[[CONFPARAM]]=MySequence");
    cout << "Sent: SETCONF=SMUSequenceName[[CONFPARAM]]=MySequence, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUStep1_Source_DCCurrent_CurrentLevel[[CONFPARAM]]=1150009");
    cout << "Sent: SETCONF=SMUStep1_Source_DCCurrent_CurrentLevel[[CONFPARAM]]=1150009, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUStep2_Measurement_ApertureTime[[CONFPARAM]]=1150058");
    cout << "Sent: SETCONF=SMUStep2_Measurement_ApertureTime[[CONFPARAM]]=1150058, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUStep3_Source_Advanced_SourceDelay[[CONFPARAM]]=1150051");
    cout << "Sent: SETCONF=SMUStep3_Source_Advanced_SourceDelay[[CONFPARAM]]=1150051, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUSequenceNumberOfSteps[[CONFPARAM]]=3");
    cout << "Sent: SETCONF=SMUSequenceNumberOfSteps[[CONFPARAM]]=3, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerFromSwitch_StartDigitalEdge[[CONFPARAM]]=/SMU/PXI_Trig1");
    cout << "Sent: SETCONF=SMUTriggerFromSwitch_StartDigitalEdge[[CONFPARAM]]=/SMU/PXI_Trig1, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerFromSwitch_SequenceAdvanceDigitalEdge[[CONFPARAM]]=/SMU/PXI_Trig1");
    cout << "Sent: SETCONF=SMUTriggerFromSwitch_SequenceAdvanceDigitalEdge[[CONFPARAM]]=/SMU/PXI_Trig1, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerToDMM_SourceCompleteEvent[[CONFPARAM]]=1030");
    cout << "Sent: SETCONF=SMUTriggerToDMM_SourceCompleteEvent[[CONFPARAM]]=1030, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerToDMM_SourceCompleteEvent_Value[[CONFPARAM]]=/SMU/PXI_Trig2");
    cout << "Sent: SETCONF=SMUTriggerToDMM_SourceCompleteEvent_Value[[CONFPARAM]]=/SMU/PXI_Trig2, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerToSwitch_SequenceIterationCompleteEvent[[CONFPARAM]]=1032");
    cout << "Sent: SETCONF=SMUTriggerToSwitch_SequenceIterationCompleteEvent[[CONFPARAM]]=1032, Obtained: " << result << endl;

    result = client.Query("SETCONF=SMUTriggerToDMM_SequenceIterationCompleteEvent_Value[[CONFPARAM]]=/SMU/PXI_Trig0");
    cout << "Sent: SETCONF=SMUTriggerToDMM_SequenceIterationCompleteEvent_Value[[CONFPARAM]]=/SMU/PXI_Trig0, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch1ResourceName[[CONFPARAM]]=2526_1");
    cout << "Sent: SETCONF=Switch1ResourceName[[CONFPARAM]]=2526_1, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch1Topology[[CONFPARAM]]=2526/2-Wire 79x1 Mux");
    cout << "Sent: SETCONF=Switch1Topology[[CONFPARAM]]=2526/2-Wire 79x1 Mux, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch1ScanList[[CONFPARAM]]=ch70:75->com");
    cout << "Sent: SETCONF=Switch1ScanList[[CONFPARAM]]=ch70:75->com, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch2ResourceName[[CONFPARAM]]=SwitchBlock1Dev1");
    cout << "Sent: SETCONF=Switch2ResourceName[[CONFPARAM]]=SwitchBlock1Dev1, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch2Topology[[CONFPARAM]]=Configured Topology");
    cout << "Sent: SETCONF=Switch2Topology[[CONFPARAM]]=Configured Topology, Obtained: " << result << endl;

    result = client.Query("SETCONF=Switch2ScanList[[CONFPARAM]]=[c2->card1r2->c26], [c3->card1r3->c27]; [c6->card1r2->c26], [c7->card1r3->c27]; [c10->card1r2->c26], [c11->card1r3->c27]; [c14->card1r2->c26], [c15->card1r3->c27]; [c18->card1r2->c26], [c19->card1r3->c27]; [c22->card1r2->c26], [c23->card1r3->c27];");
    cout << "Sent: SETCONF=Switch2ScanList[[CONFPARAM]]=[c2->card1r2->c26], [c3->card1r3->c27]; [c6->card1r2->c26], [c7->card1r3->c27]; [c10->card1r2->c26], [c11->card1r3->c27]; [c14->card1r2->c26], [c15->card1r3->c27]; [c18->card1r2->c26], [c19->card1r3->c27]; [c22->card1r2->c26], [c23->card1r3->c27];, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMResourceName[[CONFPARAM]]=DMM");
    cout << "Sent: SETCONF=DMMResourceName[[CONFPARAM]]=DMM, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMFunction_DCVolts[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMFunction_DCVolts[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMResolution[[CONFPARAM]]=0.1");
    cout << "Sent: SETCONF=DMMResolution[[CONFPARAM]]=0.1, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMRange[[CONFPARAM]]=0.1");
    cout << "Sent: SETCONF=DMMRange[[CONFPARAM]]=0.1, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMTriggerSource_TTL2[[CONFPARAM]]=4");
    cout << "Sent: SETCONF=DMMTriggerSource_TTL2[[CONFPARAM]]=4, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMTriggerSlope_RisingEdge[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMTriggerSlope_RisingEdge[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMSampleTrigger_TTL2[[CONFPARAM]]=4");
    cout << "Sent: SETCONF=DMMSampleTrigger_TTL2[[CONFPARAM]]=4, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMSampleCount[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMSampleCount[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMSampleTriggerSlope_RisingEdge[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMSampleTriggerSlope_RisingEdge[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMApertureTimeUnits_Seconds[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMApertureTimeUnits_Seconds[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMApertureTime[[CONFPARAM]]=0.010");
    cout << "Sent: SETCONF=DMMApertureTime[[CONFPARAM]]=0.010, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMNumberOfAverages[[CONFPARAM]]=1");
    cout << "Sent: SETCONF=DMMNumberOfAverages[[CONFPARAM]]=1, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMAutoZero_Off[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMAutoZero_Off[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMADCCalibration_Off[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMADCCalibration_Off[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMSettleTime[[CONFPARAM]]=0.0001");
    cout << "Sent: SETCONF=DMMSettleTime[[CONFPARAM]]=0.0001, Obtained: " << result << endl;

    result = client.Query("SETCONF=DMMControlAction_Commit[[CONFPARAM]]=0");
    cout << "Sent: SETCONF=DMMControlAction_Commit[[CONFPARAM]]=0, Obtained: " << result << endl;

    result = client.Query("SETCONF=ApplicationNumberOfWeldChannels[[CONFPARAM]]=6");
    cout << "Sent: SETCONF=ApplicationNumberOfWeldChannels[[CONFPARAM]]=6, Obtained: " << result << endl;


    result = client.Query("GETCONF=SMUResourceName");
    cout << "Sent: GETCONF=SMUResourceName, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUChannels");
    cout << "Sent: GETCONF=SMUChannels, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSourceMode_Sequence");
    cout << "Sent: GETCONF=SMUSourceMode_Sequence, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUOutputFunction_DCCurrent");
    cout << "Sent: GETCONF=SMUOutputFunction_DCCurrent, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSourceTransientResponse_Fast");
    cout << "Sent: GETCONF=SMUSourceTransientResponse_Fast, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUCurrent");
    cout << "Sent: GETCONF=SMUCurrent, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUCurrentLevelRange");
    cout << "Sent: GETCONF=SMUCurrentLevelRange, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUMeasurementSense_Local");
    cout << "Sent: GETCONF=SMUMeasurementSense_Local, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUMeasurementApertureTime");
    cout << "Sent: GETCONF=SMUMeasurementApertureTime, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSourceAdvancedSourceDelay");
    cout << "Sent: GETCONF=SMUSourceAdvancedSourceDelay, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUVoltage");
    cout << "Sent: GETCONF=SMUVoltage, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSourceAdvancedSequenceLoopCount");
    cout << "Sent: GETCONF=SMUSourceAdvancedSequenceLoopCount, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUMeasurementAdvancedDCNoiseRejection_Normal");
    cout << "Sent: GETCONF=SMUMeasurementAdvancedDCNoiseRejection_Normal, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSequenceName");
    cout << "Sent: GETCONF=SMUSequenceName, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUStep1_Source_DCCurrent_CurrentLevel");
    cout << "Sent: GETCONF=SMUStep1_Source_DCCurrent_CurrentLevel, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUStep2_Measurement_ApertureTime");
    cout << "Sent: GETCONF=SMUStep2_Measurement_ApertureTime, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUStep3_Source_Advanced_SourceDelay");
    cout << "Sent: GETCONF=SMUStep3_Source_Advanced_SourceDelay, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUSequenceNumberOfSteps");
    cout << "Sent: GETCONF=SMUSequenceNumberOfSteps, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerFromSwitch_StartDigitalEdge");
    cout << "Sent: GETCONF=SMUTriggerFromSwitch_StartDigitalEdge, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerFromSwitch_SequenceAdvanceDigitalEdge");
    cout << "Sent: GETCONF=SMUTriggerFromSwitch_SequenceAdvanceDigitalEdge, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerToDMM_SourceCompleteEvent");
    cout << "Sent: GETCONF=SMUTriggerToDMM_SourceCompleteEvent, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerToDMM_SourceCompleteEvent_Value");
    cout << "Sent: GETCONF=SMUTriggerToDMM_SourceCompleteEvent_Value, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerToSwitch_SequenceIterationCompleteEvent");
    cout << "Sent: GETCONF=SMUTriggerToSwitch_SequenceIterationCompleteEvent, Obtained: " << result << endl;

    result = client.Query("GETCONF=SMUTriggerToDMM_SequenceIterationCompleteEvent_Value");
    cout << "Sent: GETCONF=SMUTriggerToDMM_SequenceIterationCompleteEvent_Value, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch1ResourceName");
    cout << "Sent: GETCONF=Switch1ResourceName, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch1Topology");
    cout << "Sent: GETCONF=Switch1Topology, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch1ScanList");
    cout << "Sent: GETCONF=Switch1ScanList, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch2ResourceName");
    cout << "Sent: GETCONF=Switch2ResourceName, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch2Topology");
    cout << "Sent: GETCONF=Switch2Topology, Obtained: " << result << endl;

    result = client.Query("GETCONF=Switch2ScanList");
    cout << "Sent: GETCONF=Switch2ScanList, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMResourceName");
    cout << "Sent: GETCONF=DMMResourceName, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMFunction_DCVolts");
    cout << "Sent: GETCONF=DMMFunction_DCVolts, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMResolution");
    cout << "Sent: GETCONF=DMMResolution, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMRange");
    cout << "Sent: GETCONF=DMMRange, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMTriggerSource_TTL2");
    cout << "Sent: GETCONF=DMMTriggerSource_TTL2, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMTriggerSlope_RisingEdge");
    cout << "Sent: GETCONF=DMMTriggerSlope_RisingEdge, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMSampleTrigger_TTL2");
    cout << "Sent: GETCONF=DMMSampleTrigger_TTL2, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMSampleCount");
    cout << "Sent: GETCONF=DMMSampleCount, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMSampleTriggerSlope_RisingEdge");
    cout << "Sent: GETCONF=DMMSampleTriggerSlope_RisingEdge, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMApertureTimeUnits_Seconds");
    cout << "Sent: GETCONF=DMMApertureTimeUnits_Seconds, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMApertureTime");
    cout << "Sent: GETCONF=DMMApertureTime, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMNumberOfAverages");
    cout << "Sent: GETCONF=DMMNumberOfAverages, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMAutoZero_Off");
    cout << "Sent: GETCONF=DMMAutoZero_Off, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMADCCalibration_Off");
    cout << "Sent: GETCONF=DMMADCCalibration_Off, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMSettleTime");
    cout << "Sent: GETCONF=DMMSettleTime, Obtained: " << result << endl;

    result = client.Query("GETCONF=DMMControlAction_Commit");
    cout << "Sent: GETCONF=DMMControlAction_Commit, Obtained: " << result << endl;

    result = client.Query("GETCONF=ApplicationNumberOfWeldChannels");
    cout << "Sent: GETCONF=ApplicationNumberOfWeldChannels, Obtained: " << result << endl;

    auto reader = client.Register("Heartbeat");
    int count = 0;
    ServerEvent event;
    while (reader->Read(&event))
    {
        cout << "Server Event: " << event.eventdata() << endl;
        count += 1;
        if (count == 5)
        {
            client.Invoke("Reset", "");
        }
    }
    Status status = reader->Finish();
    cout << "Server notifications complete" << endl;

    cout << "Performing 4 probe measurement" << endl;
    {
        auto startTime = chrono::steady_clock::now();
        ClientContext ctx;
        FourProbeRequest request;
        FourProbeData data;
        client.m_Stub->PerformFourProbeMeasurement(&ctx, request, &data);
        auto measurements = data.data();
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "4 probe measurement took: " << elapsed.count() << " milliseconds" << endl;
        cout << "Received " << measurements.size() << " measurements." << endl;
        cout << "First Results: "  << endl;
        int x=0;
        for (auto it = measurements.begin();  it != measurements.end(); ++it)
        {
            cout << "  -V:" << (*it).negvoltage() << " +V:" << (*it).posvoltage() << " -C" << (*it).negcurrent() << " +C" << (*it).poscurrent() << " Z:" << (*it).impedance() << endl;
            if (++x == 10)
            {
                break;
            }
        }
    }
    cout << "Performing Streaming 4 probe measurement" << endl;
    {
        auto startTime = chrono::steady_clock::now();
        ClientContext ctx;
        FourProbeRequest request;
        FourProbeRaw data;
        auto measurementReader = client.m_Stub->StreamFourProbeMeasurement(&ctx, request);
        int x=0;
        cout << "First Four Probe Results: "  << endl;
        while (measurementReader->Read(&data))
        {
            if (++x <= 10)
            {
                cout << "  -V:" << data.negvoltage() << " +V:" << data.posvoltage() << " -C" << data.negcurrent() << " +C" << data.poscurrent() << " Z:" << data.impedance() << endl;
            }
        }
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "4 probe measurement took: " << elapsed.count() << " milliseconds" << endl;
        cout << "Received " << x << " measurements." << endl;
    }
}