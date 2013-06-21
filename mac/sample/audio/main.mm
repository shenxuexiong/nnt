
# include <nnt/Foundation+NNT.h>

# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

# include <nnt/Core/File+NNT.h>
# include <nnt/Parser/WavParser.h>
# include <nnt/Codec/VoicePrint.h>

# include <nnt/Trail/Micphone.h>
# include <nnt/Core/Task+NNT.h>

# include <nnt/Store/LevelDB+NNT.h>

NNT_USINGCXXNAMESPACE;

class RecordTask
: public core::Task
{
public:
    
    RecordTask()
    : recording(false)
    {
        infinite();
        dev_trail.start();
        
        au_rdr.set(dev_mic);
        au_rdr.type.set("wav");
        au_rdr.format.set_sampler(8000);
        au_rdr.format.set_channel(1);
        au_rdr.format.set_bits(8);
    }
    
    virtual int main()
    {
        dev_trail.update();
        real p = dev_trail.peak_power();
        
        if (p > -20 && !recording)
        {
            recording = true;
            trace_msg(@"recording start");
            
            // begin recording.
        }
        else if (p < -40 && recording)
        {
            sleep_second(5);
            trace_msg(@"recording ended");
            recording = false;
        }
        
        //trace_fmt(@"power: %f", p);
        ::sleep_second(1);
        return 0;
    }
 
    mic::Device dev_mic;
    mic::Recorder au_rdr;
    mic::Trail dev_trail;
    bool recording;
    
};

RecordTask task;

void test_vp()
{
    vp::Result res0, res1, res2;
    
    if (1)
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("record.wav"), da);
        parser::Wav wv;
        wv.parse(da);
    }
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res0 = dg.calc(da);
    }
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word1.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res1 = dg.calc(da);
    }
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word2.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res2 = dg.calc(da);
    }
        
    trace_fmt(@"0-1 cmp: %f", res0.compare(res1));
    trace_fmt(@"0-2 cmp: %f", res0.compare(res2));
    trace_fmt(@"1-2 cmp: %f", res1.compare(res2));
    
}

int main(int argc, char** argv)
{    
    task.start();
    
    cross::Application app;
    return app.execute(argc, argv);
}
