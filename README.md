<div id="top"></div>



<!-- PROJECT LOGO -->
<br />
<div align="center">
    <img src="images/logo.png" alt="Logo" width="500" height="360">
  <h2 align="center">Application Using Main Window</h2>
  <h3 align="center">Create a MainWindow based application using the designer</h3>
</div>



<!-- TABLE OF CONTENTS -->
<summary>Table of Contents</summary>
  <ol>
        <li><a href="#SpreadSheet">SpreadSheet (Functionality)</a></li>
           <ul> 
              <li><a href="#Context">Context</a></li>
                  <ul> 
                    <li><a href="#Remarks">Remarks</a></li>           
                  </ul>
              <li><a href="#Go-Cell">Go Cell</a></li>
              <li><a href="#Find-Dialog">Find Dialog</a></li>
              <li><a href="#Saving-and-loading-files">Saving and loading files</a></li>
                  <ul> 
                    <li><a href="#Saving-Content">Saving Content</a></li>
                    <li><a href="#Save-File-action">Save File action</a></li>
                    <li><a href="#Load-File">Load File</a></li>
                  </ul>
              <li><a href="#other-actions">Other Actions</a></li>
                  <ul> 
                    <li><a href="#Copy">Copy</a></li>
                    <li><a href="#Cut">Cut</a></li>
                    <li><a href="#Paste">Paste</a></li>
                    <li><a href="#Delete">Delete</a></li>    
                  </ul>
            </ul>
              <li><a href="#Text-Editor">Text Editor</a></li>
                  <ul> 
                    <li><a href="#Creating-the-project">Creating the project</a></li>
                    <li><a href="#Icons">Icons</a></li>
                    <li><a href="#Menus">Menus</a></li>
                    <li><a href="#Actions">Actions</a></li>
                    <li><a href="#Functionality">Functionality</a></li>  
                 </ul>  
    </ol>



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- GETTING STARTED -->
### Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

1. [**How to install Qt**](https://anassbelcaid.github.io/CS221/qtcreator/)
2. **Clone the repo**
   ```sh
   git clone https://github.com/IlyasKadi/HSLA_Image_color_space.git
   ```

<p align="right">(<a href="#top">back to top</a>)</p>


# SpreadSheet
## Context
In the lecture on **QMainWindow**, we wrote the code for the graphical and set of actions for our main SpreadSeet application. Now we will focus on writing a set of basic functionality.

  In the our last iteration of the SpreadSheet we did obtain an application with:
   * Menu Bar
   * Two tools bars
   * Status bar to print the informations

You should have an application that looks like that :
   
   <p align="center">
     <img src="images/hsl_hue.png">
   </p>  
   
   >The Hue representation of basic colors. 
        
   **Saturation** (denoted as `s`) indicates the degree to which the hue differs from a neutral gray. The values run from $0\%$, which is no color saturation, to $100\%$, which is the fullest saturation of a given hue at a given percentage of illumination.
   
   <p align="center">
     <img src="images/hsl_saturation.png">
   </p>  
   
   >The saturation field in the HSL space.
   
   **Luminance** (denoted as `l`) indicates the level of illumination.
   The value values run as pecentenage $0\%$ appears black (no light) while $100/%$ is full illumination.
   
   <p align="center">
     <img src="images/hsl_lightness.png">
   </p>  
  
<p align="right">(<a href="#top">back to top</a>)</p>

### Remarks

We did add the following modifications:

   1. The `updateStatusBar` now takes two ints in order to syncrhonize with the selected item from the spreadsheet.
  
 ```cpp
  void updateStatusBar(int, int) 
 ```

Here is the **implementation** of this function:

```cpp
   void SpreadSheet::updateStatusBar(int row, int col)
    {
     QString cell{"(%0, %1)"};
     cellLocation->setText(cell.arg(row+1).arg(col+1));
    }
```
Which simply change the **cellLocation** text with the current cell coordinates.

   1. We added the `makeConnexion()` function to connect all the actions. Here is the content of the this function:
    
```cpp
  void SpreadSheet::makeConnexions()
  {
  // --------- Connexion for the  select all action ----/
  connect(all, &QAction::triggered,
          spreadsheet, &QTableWidget::selectAll);
  // Connection for the  show grid
  connect(showGrid, &QAction::triggered,
          spreadsheet, &QTableWidget::setShowGrid);
  //Connection for the exit button
  connect(exit, &QAction::triggered, this, &SpreadSheet::close);
  //connectting the chane of any element in the spreadsheet with the update status bar
  connect(spreadsheet, &QTableWidget::cellClicked, this,  &SpreadSheet::updateStatusBar);
  }
 ```

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Inhertance diagram -->
## Inhertance-diagram

Your goal is to write additional classes that inherit from this class and implement addtional functionalities.

<p align="center">
  <img src="images/image_class_diagram.png">
</p>

 >UML class diagram for the additional Images classes.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Image -->
## Image
Create a class named `Image` that inherits from the `PNG` class. This means that your class will inherits all the attributes and members from the `PNG` class. Meaning that anything you can do with a `PNG` you can do with an `Image`.
  

.Header
```cpp
class Image : public PNG
{
public:
    using PNG::PNG;
    Image(string filename);
    void lighten(double amount=0.1);
    void saturate(double amount);
    void rotateColor(double angle);
};
```
<p align="right">(<a href="#top">back to top</a>)</p>

### lighten

* `lighten(double amount)` changes the luminance of each pixel by amount.

original | lighten
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/lighten.png)

>Effect of adding 0.2 light on the image. 

.cpp
```cpp
void Image::lighten(double amount)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.l += amount;
            p.l = (p.l>0) ? p.l:0;
            p.l = (p.l<=1)? p.l:1;
        }
    }
}
```

<p align="right">(<a href="#top">back to top</a>)</p>

### saturate

* `saturate` changes the **luminance** by amount. 

original | saturate
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/saturate.png)

>Effect of adding 0.2 light on the image. 

.cpp
```cpp
void Image::saturate(double amount)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.s += amount;
            p.s = (p.s>0) ? p.s:0;
            p.s = (p.s<=1)? p.s:1;
        }
    }
}
```

<p align="right">(<a href="#top">back to top</a>)</p>

### rotateColor

* `rotateColor(double angle)`: add the value of angle to each pixel.

original | rotateColor
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/rotateColor.png)

>Effect of rotating the image by 90 degrees. 

.cpp
```cpp
void Image::rotateColor(double angle)
{
    for(unsigned i=0;i< width();i++)
    {
        for(unsigned j=0;j<height();j++)
        {
            HSLAPixel &p  = getPixel(i,j);
            p.h += angle;
            while (p.h>360)
                p.h=p.h-360;
            while (p.h<0)
                p.h=p.h+360;
        }
    }
}
```


<p align="right">(<a href="#top">back to top</a>)</p>


<!-- Grayscale -->
## Grayscale

Now you should write a simple class `Grayscale` that inherits from the `Image` class. This is a simple class that eliminates all the colors and represents the image using only a `grayscale` level.

original | Grayscale
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/Grayscale.png)

>Effect of reducing the saturation of each pixel. 

.Header 
```cpp
class Grayscale : public Image
{
public:
     using Image::Image;
     using PNG::writeToFile;
     Grayscale(string filename);
};
``` 
.cpp
```cpp
Grayscale::Grayscale(string filename):Image(filename)
{
    readFromFile(filename);
    saturate(-1);
}
```

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Illini -->
## Illini

Create a class called `Illini` that inherits from the `Image` class. An `Illini` image has only two colors that are defined as attributes.

We divided the hue cercle into the closest arc to the first color (in this case orange h=11), and the one close to the second color (in this case blue h=216)

![Image illini](images/illini1.jpeg)

original | Illini
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/Illini.png)

>Illini Image which only stores two color (in this case blue and orange).

.Header
```cpp
class Illini : public Image
{
public:
    using Image ::Image;
    int color1 =11;
    int color2 =216;
    Illini(string filename,int color1=11,int color2=216);
};
```

.cpp
```cpp
Illini::Illini(string filename,int col1,int col2):Image(filename)
{
    this->color1=col1;
    this->color2=col2;
    readFromFile(filename);
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         int ma_hue=max(color1,color2);
         int mi_hue=min(color1,color2);
         int half_r_dist=(ma_hue-mi_hue)/2;
         int half_l_dist=(360-ma_hue+mi_hue)/2+ma_hue;
        P.h= (P.h>half_r_dist && P.h<=half_l_dist) ?ma_hue:mi_hue;
      }
}
```
<p align="right">(<a href="#top">back to top</a>)</p>

## Spotlight

A `Spotlight` image create a **spotlight** centered at a given point `centerX, centerY` defined as attributes.

original | Spotlight
------------ | -------------
![Image haikyuu](images/haikyuu.png) | ![Image haikyuu](images/Spotlight.png)
>Illustration of the spotlight effect. 

.Header
```cpp
class Spotlight : public Image
{
public:
    using Image::Image;
    int centerX;
    int centerY;
    Spotlight(string filename, int centX, int centY);
    void changeSpotPoint(int cX, int cY);
};
```

.cpp
```cpp
Spotlight::Spotlight(string filename,int centX, int centY):Image(filename)
{
    this->centerX=centX;
    this->centerY=centY;
    readFromFile(filename);
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         double dist = sqrt(((x-centerX)*(x-centerX))+((y-centerY)*(y-centerY)));
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         if(dist<160)
              P.l=P.l*(1-dist*0.005);
         else
            P.l=0.2*P.l;
      }
}
```
## ChangeSpotPoint

Spotlight | ChangeSpotPoint
------------ | -------------
![Image haikyuu](images/Spotlight.png) | ![Image haikyuu](images/ChangeSpotPoint.png)

After completing the all the tests, add a method

```cpp
void changeSpotPoint(int centerX, int centerY)
```

That changes the position of the spotlight.
```cpp
void Spotlight::changeSpotPoint(int cX, int cY)
{
    for(unsigned x = 0; x < width() ; x++)
      for(unsigned y = 0; y < height(); y++)
      {
         double O_dist = sqrt(((x-centerX)*(x-centerX))+((y-centerY)*(y-centerY)));
         double N_dist = sqrt(((x-cX)*(x-cX))+((y-cY)*(y-cY)));
         //reference on the pixel
         HSLAPixel &P = getPixel(x, y);
         //modifiy the element of P
         if(O_dist>=160)
             P.l=5*P.l;
         else
            P.l=P.l/(1-O_dist*0.005);

         if(N_dist>=160)
             P.l=0.2*P.l;
         else
            P.l=P.l*(1-N_dist*0.005);
      }
}
```

Out Team - [AIT EL KADI Ilyas](https://github.com/IlyasKadi) - [AZIZ Oussama](https://github.com/ATAMAN0)

Project Link: [https://github.com/IlyasKadi/HSLA_Image_color_space](https://github.com/IlyasKadi/HSLA_Image_color_space)

<p align="right">(<a href="#top">back to top</a>)</p>

> Excellent Work!! One of the best reports I've read so far!
