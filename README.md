# MPM3D-UMAT

MPM3D-UMAT is the User Defined Material interface for the 3D explicit and parallel MPM code, [MPM3D][mpm3d], developed since 2004 in the [Computational Dynamics Laboratory][comdyn] led by Professor [Xiong Zhang][xzhang] at Tsinghua University in China.  MPM3D-UMAT provides users a convenient way to define a new constitutive model.

## How to use it

1. Clone or [download][download] the source code from the [github repository][github-mpm3d-umat].
2. Use [cmake][cmake] to generate the native makefiles and workspaces that can be used in the compiler environment of your choice.
3. Compile the source code and generate the DLL file (usermat.dll).
4. Replace the DLL file with the same name in the MPM3D binary directory.

## How to define a new constitutive model

MPM3D supports at most five user defined constitutive models.  The material names in the input data file (.xmp file) are assigned as **UserMaterial1** to **UserMaterial5**. A typical input format is

```xml
<Material name="elastic">
  <ReferenceDensity value="1e3" />
  <StrengthModel type="UserMaterial1" Young="4.2e6" Poisson="0.4"/>
  <EquationOfState type="none"/>
  <FailureModel type="none" />
</Material>
```

To define a constitutive model, two kinds of variables must be considered: material parameters and historical variables. 



The material parameters are provided by users in the input data file.  The data structure has been predefined in the header file *UserMatX.h* as a hash table.

```c++
map<string, double> Parameters;
```

In the source file *UserMatX.cpp*, users are supposed to initialize the key values as the parameters’ name in the constructor. The names are used in the input data file and MPM3D will automatically read the value from it.

```c++
// An example of material parameters
// UserMat1.cpp 
USERMAT1::USERMAT1(){
  Parameters["E"] = 0.0;
  Parameters["Mu"] = 0.2;
}
```

```xml
<!-- An example of input data file for UserMat1 -->
<StrengthModel type="UserMaterial1" E="2.1e11" Mu="0.3"/>
```



The historical variables are carried by particles and updated by user defined functions. Particle-carried variables are defined in the header file *Prop.h*. Except for the pre-assigned variables, other historical variables are stored in the array **UserValue**.

```c++
double* UserValue;
```

In the user defined material constructor, users are supposed to define the total number of the historical values.

``` c++
USERMAT1::USERMAT1(){
  UserDefinedNum = 0;
}
```

To illustrate how to write an user defined material model, the USERMAT1 and USERMAT2 have been implemented as the linear elasticity and Drucker–Prager model.

[cmake]:https://cmake.org/
[mpm3d]:http://comdyn.hy.tsinghua.edu.cn/show/software/581-mpm3d-install
[comdyn]:http://comdyn.hy.tsinghua.edu.cn/english
[xzhang]:http://comdyn.hy.tsinghua.edu.cn/english/xzhang
[github-mpm3d-umat]:https://github.com/xzhang66/MPM3D-UMAT
[download]:https://github.com/xzhang66/MPM3D-UMAT/archive/master.zip

