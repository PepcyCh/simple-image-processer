## MVVM

### Common

图像类

### Model

一个图像的 vector

图像处理函数

### View

UI

### ViewModel

持有 Model（或 Model 的引用）

向 View 提供要绑定的函数，比如加载的函数、修改的函数

### App

创建 M、V、VM 的对象，把 VM 提供的函数绑定给 V

把 M 给 VM，如果 VM 持有的是引用的话

### 分工

* Model、ViewModel - cyw
* App - zxn
* View - hqy

## 迭代

* [x] 导入导出
* [ ] 黑白图像与二值图像
  * [ ] 黑白化
  * [ ] 二值化
* [ ] 图像增强（模糊、锐化等）
  * [ ] 锐化
  * [ ] 模糊
  * [ ] 直方图均值化
  * [ ] 显示直方图
* [ ] 几何变形
  * [ ] 旋转
  * [ ] 缩放
  * [ ] 切变