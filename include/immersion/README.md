# immersion C++ OpenGL game engine

设计目标：**让学过C++算法与数据结构但不熟悉OpenGL的人，能快速上手做游戏。**

换言之，我希望 *让输出图像与声音像printf一样方便。同时也能够进行精细的画面控制*。

设计思路：

* 采用分层式的架构，分为模型层，绘图层，C高级抽象层，C++ Entity Component System层，项目模版。
* 素材层负责加载、定义待绘制的游戏素材。如2D图像，3D模型，声音等。
* 绘图层负责将素材（指针）渲染到游戏世界中。
* 提供类似draw("a.jpg",left,top,bottom,right)的高级函数（似无必要）
* 提供 RenderSystem，渲染所有Renderabl的Entity Component
* 提供一个CMake项目模板，因为设置一个项目环境本身也是非常复杂且无趣的。
* Header only design.

全局共享一个Camera（目前还没有发现需要多个Camera的情况），采用OpenGL的右手坐标系。
