#ifndef VMINIAUDIO_VAUDIO_H
#define VMINIAUDIO_VAUDIO_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VMA_VERSION_MAJOR 0
#define VMA_VERSION_MINOR 1
#define VMA_VERSION_PATCH 0

#define VMA_VERSION_STRING "0.1.0"
#define VMA_NAME "V-MiniAudio"

#if defined(_WIN32)
    #if defined(VMA_BUILD_DLL)
        #define VMA_API __declspec(dllexport)
    #elif defined(VMA_USE_DLL)
        #define VMA_API __declspec(dllimport)
    #else
        #define VMA_API
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define VMA_API __attribute__((visibility("default")))
#else
    #define VMA_API
#endif

typedef enum VMAResult {
    VMA_SUCCESS = 0,
    VMA_ERROR_UNKNOWN = -1,
    VMA_ERROR_INVALID_ARGUMENT = -2,
    VMA_ERROR_OUT_OF_MEMORY = -3,
    VMA_ERROR_NOT_INITIALIZED = -4,
    VMA_ERROR_ALREADY_INITIALIZED = -5,
    VMA_ERROR_FILE_NOT_FOUND = -6,
    VMA_ERROR_FILE_READ = -7,
    VMA_ERROR_FILE_WRITE = -8,
    VMA_ERROR_UNSUPPORTED_FORMAT = -9,
    VMA_ERROR_INVALID_FORMAT = -10,
    VMA_ERROR_DEVICE_NOT_FOUND = -11,
    VMA_ERROR_DEVICE_INIT = -12,
    VMA_ERROR_DEVICE_LOST = -13,
    VMA_ERROR_PLAYBACK = -14,
    VMA_ERROR_DECODING = -15,
    VMA_ERROR_ENCODING = -16,
    VMA_ERROR_NOT_SUPPORTED = -17,
    VMA_ERROR_INVALID_STATE = -18,
    VMA_ERROR_END_OF_STREAM = -19
} VMAResult;

typedef enum VMAAudioFormat {
    VMA_FORMAT_UNKNOWN = 0,
    VMA_FORMAT_WAV,
    VMA_FORMAT_MP3,
    VMA_FORMAT_OGG,
    VMA_FORMAT_FLAC,
    VMA_FORMAT_PCM
} VMAAudioFormat;

typedef enum VMASampleFormat {
    VMA_SAMPLE_UNKNOWN = 0,
    VMA_SAMPLE_U8,
    VMA_SAMPLE_S16,
    VMA_SAMPLE_S24,
    VMA_SAMPLE_S32,
    VMA_SAMPLE_F32,
    VMA_SAMPLE_F64
} VMASampleFormat;

typedef enum VMAPlaybackState {
    VMA_STATE_STOPPED = 0,
    VMA_STATE_PLAYING,
    VMA_STATE_PAUSED,
    VMA_STATE_FINISHED
} VMAPlaybackState;

typedef enum VMALogLevel {
    VMA_LOG_NONE = 0,
    VMA_LOG_ERROR,
    VMA_LOG_WARNING,
    VMA_LOG_INFO,
    VMA_LOG_DEBUG,
    VMA_LOG_TRACE
} VMALogLevel;

typedef struct VMAContext VMAContext;
typedef struct VMAAudio VMAAudio;
typedef struct VMADevice VMADevice;

typedef struct VMAConfig {
    uint32_t sample_rate;
    uint32_t channels;
    uint32_t buffer_frames;
    VMASampleFormat sample_format;
    bool enable_logging;
    bool enable_low_latency;
} VMAConfig;

typedef struct VMAAudioInfo {
    VMAAudioFormat format;
    VMASampleFormat sample_format;
    uint32_t sample_rate;
    uint32_t channels;
    uint64_t total_frames;
    double duration;
    uint64_t file_size;
} VMAAudioInfo;

typedef struct VMADeviceInfo {
    char name[256];
    char id[256];
    uint32_t max_channels;
    uint32_t preferred_sample_rate;
    bool is_default;
} VMADeviceInfo;

typedef void (*VMALogCallback)(
    VMALogLevel level,
    const char* message,
    void* user_data
);

typedef void (*VMAFinishedCallback)(
    VMAAudio* audio,
    void* user_data
);

typedef void (*VMAAudioCallback)(
    float* output,
    uint32_t frames,
    uint32_t channels,
    void* user_data
);

VMA_API const char* vma_get_version(void);
VMA_API const char* vma_get_name(void);
VMA_API const char* vma_result_string(VMAResult result);

VMA_API void vma_config_init(VMAConfig* config);

VMA_API VMAResult vma_init(
    VMAContext** context,
    const VMAConfig* config
);

VMA_API void vma_shutdown(VMAContext* context);

VMA_API bool vma_is_initialized(
    const VMAContext* context
);

VMA_API VMAResult vma_update(
    VMAContext* context
);

VMA_API VMAResult vma_audio_load(
    VMAContext* context,
    const char* path,
    VMAAudio** audio
);

VMA_API VMAResult vma_audio_load_memory(
    VMAContext* context,
    const void* data,
    size_t size,
    VMAAudio** audio
);

VMA_API VMAResult vma_audio_create_pcm(
    VMAContext* context,
    const void* samples,
    uint64_t frame_count,
    uint32_t channels,
    uint32_t sample_rate,
    VMASampleFormat format,
    VMAAudio** audio
);

VMA_API void vma_audio_destroy(
    VMAAudio* audio
);

VMA_API VMAResult vma_audio_play(
    VMAAudio* audio
);

VMA_API VMAResult vma_audio_pause(
    VMAAudio* audio
);

VMA_API VMAResult vma_audio_resume(
    VMAAudio* audio
);

VMA_API VMAResult vma_audio_stop(
    VMAAudio* audio
);

VMA_API VMAResult vma_audio_restart(
    VMAAudio* audio
);

VMA_API VMAPlaybackState vma_audio_get_state(
    const VMAAudio* audio
);

VMA_API bool vma_audio_is_playing(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_set_volume(
    VMAAudio* audio,
    float volume
);

VMA_API float vma_audio_get_volume(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_set_pan(
    VMAAudio* audio,
    float pan
);

VMA_API float vma_audio_get_pan(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_set_pitch(
    VMAAudio* audio,
    float pitch
);

VMA_API float vma_audio_get_pitch(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_set_looping(
    VMAAudio* audio,
    bool looping
);

VMA_API bool vma_audio_is_looping(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_seek(
    VMAAudio* audio,
    double seconds
);

VMA_API double vma_audio_get_position(
    const VMAAudio* audio
);

VMA_API double vma_audio_get_duration(
    const VMAAudio* audio
);

VMA_API VMAResult vma_audio_get_info(
    const VMAAudio* audio,
    VMAAudioInfo* info
);

VMA_API VMAResult vma_audio_set_finished_callback(
    VMAAudio* audio,
    VMAFinishedCallback callback,
    void* user_data
);

VMA_API VMAResult vma_set_master_volume(
    VMAContext* context,
    float volume
);

VMA_API float vma_get_master_volume(
    const VMAContext* context
);

VMA_API VMAResult vma_set_muted(
    VMAContext* context,
    bool muted
);

VMA_API bool vma_is_muted(
    const VMAContext* context
);

VMA_API VMAResult vma_device_get_count(
    VMAContext* context,
    uint32_t* count
);

VMA_API VMAResult vma_device_get_info(
    VMAContext* context,
    uint32_t index,
    VMADeviceInfo* info
);

VMA_API VMAResult vma_device_set_default(
    VMAContext* context
);

VMA_API VMAResult vma_device_set_by_id(
    VMAContext* context,
    const char* device_id
);

VMA_API VMAResult vma_set_audio_callback(
    VMAContext* context,
    VMAAudioCallback callback,
    void* user_data
);

VMA_API void vma_set_log_callback(
    VMAContext* context,
    VMALogCallback callback,
    void* user_data
);

VMA_API void vma_set_log_level(
    VMAContext* context,
    VMALogLevel level
);

VMA_API VMALogLevel vma_get_log_level(
    const VMAContext* context
);

VMA_API uint32_t vma_get_sample_rate(
    const VMAContext* context
);

VMA_API uint32_t vma_get_channels(
    const VMAContext* context
);

VMA_API uint32_t vma_get_buffer_frames(
    const VMAContext* context
);

#ifdef __cplusplus
}
#endif

#endif
