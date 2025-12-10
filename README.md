Modern City View: An Animated Urban Waterfront

This is my Computer Graphics project for Fall - 2025

Daffodil International University

# Modern City View: An Animated Urban Waterfront Scene

A 2D computer graphics application demonstrating fundamental graphics programming concepts through an interactive, animated urban waterfront environment.

## Features

- **Graphics Algorithms**: DDA line drawing (train headlights), Midpoint Circle Algorithm (sun/moon)
- **Animation System**: 7 simultaneously moving objects (train, 4 cars, boat, 2 clouds) at 20 FPS
- **Interactive Controls**: Day-night cycle toggle with conditional rendering effects
- **Scene Composition**: Multi-layered buildings, bridge infrastructure, water reflections, architectural details

## Quick Start

**Compile & Run (macOS):**
```bash
g++ main.cpp -o program -DGL_SILENCE_DEPRECATION -framework OpenGL -framework GLUT
./program
```

**Linux:**
```bash
g++ main.cpp -o program -lGL -lGLU -lglut
./program
```

**Windows (MinGW):**
```bash
g++ main.cpp -o program -lopengl32 -lglu32 -lglut32
program.exe
```

## Controls

| Key | Action |
|-----|--------|
| `n` | Toggle day-night cycle |
| `ESC` | Exit |

## System Requirements

- OpenGL 2.1 compatible graphics
- 2GB RAM, dual-core processor
- macOS, Linux, or Windows

## Project Structure

- **Color Palette**: 40+ centralized RGB colors
- **Buildings**: Multi-layer depth system (5 background, 4 foreground)
- **Infrastructure**: Elevated metro bridge, road, waterway
- **Animation**: Train, cars, boat, clouds with independent velocities
- **Effects**: Headlights, water reflections, stars, day-night transitions

## Educational Value

- Algorithm implementation (DDA, Midpoint Circle)
- 2D transformations and matrix operations
- Scene composition and visual design
- Real-time animation and state management
- Professional code architecture

## Technical Details

- **Lines of Code**: ~3,500
- **Resolution**: 1920×1080 pixels
- **Frame Rate**: 20 FPS (±2ms variance)
- **Memory Usage**: <50MB

## Day-Night Features

**Day Mode**: Bright blue sky, cyan water, golden sun, natural lighting

**Night Mode**: Dark navy sky, deep water, crescent moon, vehicle headlights, star field, yellow building labels

---

**Status**: Complete & Functional ✓  
**Platform**: macOS, Linux, Windows  
**Graphics API**: OpenGL 2.1 + GLUT

