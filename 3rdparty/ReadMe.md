# 基于 Anaconda 的创建 VS 2017/9 开发环境创建

- 创建环境
```
conda env create -n openblas -f environment-openblas-fixed.yml
```

- 完成后，拷贝一些文件

```
conda activate openblas
robocopy ./ %CONDA_PREFIX% h2o.cmake
robocopy ./ %CONDA_PREFIX%/Library/plugins applocal.ps1
robocopy ./ %CONDA_PREFIX%/Library/plugins qtdeploy.ps1
robocopy ./ %CONDA_PREFIX% applocal.ps1
```
