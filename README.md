# V-MiniAudio

A lightweight audio framework developed from scratch in C11, focused on audio processing and control.

How It Works

V-MiniAudio uses an audio engine to process PCM audio data through buffers.

The audio system is divided into three main components:

- VAudio: Manages audio initialization, configuration, volume and errors.
- VAudioEngine: Handles audio buffers, mixing, gain and audio processing.
- VAudioPlayer: Will manage audio playback, pausing, stopping and looping.

Audio System

The audio processing system follows a simple structure:

Audio Source
     |
     v
Audio Player
     |
     v
Audio Engine
     |
     v
PCM Processing
     |
     v
Audio Output

The engine currently supports PCM buffer processing using 32-bit floating-point samples.

Audio playback and native device output are still under development.

Features

- Written entirely in C11
- Lightweight audio processing
- PCM audio buffers
- Audio mixing
- Volume control
- Audio callbacks
- Cross-platform architecture
- No external audio libraries

Platforms

V-MiniAudio is designed for Windows, Linux, macOS and Android.

Platform-specific audio backends are planned.

License

See the LICENSE file for more information.
