#ifndef CHANNEL_H
#define CHANNEL_H

#include "channelbase.h"
#include "videodev_myth.h" // needed for v4l2_std_id type

using namespace std;

#define FAKE_VIDEO 0

class TVRec;

// Implements tuning for analog TV cards (both software and hardware encoding)
// using the V4L driver API
class Channel : public ChannelBase
{
 public:
    Channel(TVRec *parent, const QString &videodevice);
    virtual ~Channel(void);

    bool Open(void);
    void Close(void);

    // Sets
    void SetFd(int fd); 
    void SetFormat(const QString &format);
    int  SetDefaultFreqTable(const QString &name);
    bool SetChannelByString(const QString &chan); 
    bool SetChannelByDirection(ChannelChangeDirection);

    // Gets
    int  GetFd() const { return videofd; }
    QString GetDevice() const { return device; }

    // Commands
    void SwitchToInput(int newcapchannel, bool setstarting);

    // Picture attributes.
    void SetBrightness();
    void SetContrast();
    void SetColour();
    void SetHue();
    int  ChangeBrightness(bool up);
    int  ChangeColour(bool up);
    int  ChangeContrast(bool up);
    int  ChangeHue(bool up);

    // PID caching
    void SaveCachedPids(const pid_cache_t&) const;
    void GetCachedPids(pid_cache_t&) const;

  private:
    // Helper Sets
    void SetColourAttribute(int attrib, const char *name);
    void SetFreqTable(const int index);
    int  SetFreqTable(const QString &name);

    // Helper Gets
    unsigned short *GetV4L1Field(int attrib, struct video_picture &vid_pic);
    int  GetChanID() const;
    int  GetCurrentChannelNum(const QString &channame);

    // Helper Commands
    int  ChangeColourAttribute(int attrib, const char *name, bool up);
    bool TuneTo(const QString &chan, int finetune);
    bool TuneToFrequency(int frequency);

  private:
    // Data
    QString     device;
    int         videofd;

    struct CHANLIST *curList;  
    int         totalChannels;

    bool        usingv4l2;      ///< Set to true if tuner accepts v4l2 commands
    int         videomode_v4l1; ///< Current video mode if 'usingv4l2' is false
    v4l2_std_id videomode_v4l2; ///< Current video mode if 'usingv4l2' is true

    QString     currentFormat;

    int         defaultFreqTable;
};

#endif
