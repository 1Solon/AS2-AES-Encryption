# C Dev Container

This is a C development container for Visual Studio Code, it contains the following tools:

* [gcc](https://gcc.gnu.org/)
* [cmake](https://cmake.org/)
* [clangd](https://clangd.llvm.org/)

This container is heavily based on [f-squirrel's](https://github.com/f-squirrel) work, they deserve all the credit for their great explanations!

* [dockerized-cpp-build](https://ddanilov.me/dockerized-cpp-build)
* [dockerized-cpp-build-with-vscode](https://ddanilov.me/dockerized-cpp-build-with-vscode)
  
## How to use

First, open the project in visual studio code. You should then get a prompt to open the project in a container. If you don't get the prompt, you can open the command palette and run the command `Remote-Containers: Reopen in Container`.

Next, run the following command:

```bash
cd ./build && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && make
```

You can then use `make` to build the project. The executable will be deposited in the [build](/build/) directory.

## Adding extensions

You can add additional extensions by either editing [devcontainer.json](/.devcontainer/devcontainer.json) or by (inside the running devcontainer) using the right click menu on the extensions tab.

## Important

This container was built mainly for use in a class- I'm by no means a C developer, or even particularly experienced, if you do end up using this container I'd recommend you take a look at the [CMakeLists](./CMakeLists.txt) and [Dockerfile](/.devcontainer/dockerfile) and make sure it's doing what you want it to do. Please feel free to open an issue if you have any suggestions. Thanks in advance!
