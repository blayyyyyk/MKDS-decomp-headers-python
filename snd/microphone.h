#pragma once

#define MIC_SAMPLE_BUFFER_SIZE  1024

// Sampling type definitions
typedef enum _MICSamplingType
{
    MIC_SAMPLING_TYPE_8BIT = 0,        //  8 bit sampling
    MIC_SAMPLING_TYPE_12BIT,           // 12 bit sampling
    MIC_SAMPLING_TYPE_SIGNED_8BIT,     // Signed 8-bit sampling
    MIC_SAMPLING_TYPE_SIGNED_12BIT,    // Signed 12-bit sampling
    MIC_SAMPLING_TYPE_12BIT_FILTER_OFF,
    MIC_SAMPLING_TYPE_SIGNED_12BIT_FILTER_OFF,
    MIC_SAMPLING_TYPE_MAX
}
_MICSamplingType;

// Auto-sampling setting definitions
typedef struct _MICAutoParam
{
    _MICSamplingType type;              // Sampling type
    void   *buffer;                    // Pointer to result storage buffer
    u32     size;                      // Buffer size
    u32     rate;                      // Sampling period (ARM7 clock count)
    BOOL    loop_enable;               // Enable/disable loop when buffer is full
    u32 full_callback;         // Callback when buffer is full
    void   *full_arg;                  // Argument to specify for the above callbacks

}
_MICAutoParam;

typedef struct
{
    s8 sampleBuffer[MIC_SAMPLE_BUFFER_SIZE];
    _MICAutoParam autoParam;
    int frameCounter;
} mic_t;

void mic_init(void);
void mic_initAutoSampling(mic_t* mic);
void mic_finalize(mic_t* mic);
void mic_startAutoSampling(mic_t* mic);
void mic_stopAutoSampling(mic_t* mic);
int mic_update(mic_t* mic);
void mic_handlePreSleep(mic_t* mic);
void mic_handlePostSleep(mic_t* mic);