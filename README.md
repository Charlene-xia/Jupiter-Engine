# Jupiter-Engine
My own game engine. I wrote everything from scratch

## Folder Structure
This applies to both Engine and Client Project directory
| Folder              | Duties                                                                                                               |
|:-------------------:|:--------------------------------------------------------------------------------------------------------------------:|
| Assets              | Stores all types of non-code assets. Game scripts, textures, models, levels, Json data sheets, Sounds, Shaders, etc  |
| Documents           | Both written and auto generated by Doxygen                                                                           |
| Source              | Source C++ code builds Jupiter Engine                                                                                |
| Tools               | Code projects thats outside of Jupiter, served as tools to support Jupiter Engine's development                      |
| Generated           | Generated Output executables, Lib, Intermediate, Temp Files. Can be deleted then regenerated                         |
| Visual Studio Files | Generated Visual Studio Projects, Filters, Solutions, Users, etc. Can be deleted then regenerated                    |

## Source Code
| Folder              | Duties                                                                                                               |
|:-------------------:|:--------------------------------------------------------------------------------------------------------------------:|
| AI                  | Artificial Intelligense, such as behavior trees, utility theory system                                               |
| Animation           | Controlling a character's pose                                                                                       |
| ApplicationLayer    | Different platform's application entry points, Application, Window                                                   |
| Assets              | Managing all types of assets importing & exporting, sound, modeling, materials, shaders,                             |
| Audio               | Managing Sound and Audio playing                                                                                     |
| Cinematics          | Controlling Cinematic Screens, managing sequences, channels, properties                                              |
| Core                | Essential programming libraries. Math, Containers, Timing, Strings, Ptrs                                             |
| Debugging           | Debug only features. Will be excluded on non-Debugging Configs. Assertion, Logging                                   |
| Deploying           | Builds and deploy executables to different platforms                                                                 |
| Editor              | Editor only Tools. Will be excluded on releasing builds                                                              |
| Framework           | Gameplay 3Cs, Entity Component System, Event System,                                                                 |
| Input               | Managing multi-platform input, mouse, keyboards, controller for different consoles                                   |
| Modeling            | Creating and Building Meshes                                                                                         |
| Networking          | Sending and recieving network messages                                                                               |
| Physics             | Collsion, Raycasts, Gravity                                                                                          |
| Profiling           | Profiling config only. Will be excluded on non-Profiling configs. Performance Profiling for optimizations techniques |
| Rendering           | 2D and 3D Graphics Rendering, shader programming, textures, materials                                                |
| Scripting           | Node Based Visual Scripting, Lua Scripting                                                                           |
| UIUX                | User Interface and Experience, Widgets, HUD                                                                          |
| VFX                 | Visual Effects. Particles, Fog, Water, Smoke, Reflection                                                             |

## Coding Standards
- An object's life cycle should be named as the following:
  - Init
  - Update
  - Clear
  - OnEvent 

- A class should follow this order
    class Example
    {
    public:
        TypeDefs
        Enums

    private:
        Member Variables

    public:
        6 generated member functions

        APIs

    private:
        Internal functions
    }