#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<quickopencv.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	/*imread(1,2) 
	第二个参数的功能：
	* IMREAD_GRAYSCALE：加载灰度图像
	* IMREAD_UNCHANGED：加载带有透明通道的，通道数不会变
	* IMREAD_ANYCOLOR:如果是一个hsv空间的图，就可以使用这个加载
	* IMREAD_ANYDEPTH：可以加载8位，16位，32位的图像
	加载进来的是3通道的图片，每个通道一个字节（8位），共24位
	查看类型的时候会显示为枚举类型-1
	读进来的顺序为：BGR
	*/
	//string src = "C:/Users/Administrator/Desktop/output.mp4";
	Mat image = imread("C:/Users/Administrator/Desktop/wallpaper/fe5827c1b937d3b67b128fe6eb91abb0.jpg"); 
	
	if (image.empty()) {  // 判断图片是否为空，经常使用的，不做异常处理的话，下面会报错
		printf("could not load image...\n");
		return -1;
	}

	namedWindow("hello", WINDOW_FREERATIO);  //自由调整窗口大小
	imshow("hello", image);

	QuickDemo qd;
	// qd.colorSpace_Demo(image);
	//qd.mat_creation_demo(image);
	//qd.pixel_visit_demo(image);
	//qd.operators_demo(image);
	//qd.tracking_bar_demo(image);
	//qd.key_demo(image);
	//qd.color_style_demo(image);
	//qd.bitwise_demo(image);
	//qd.channels_demo(image);
	//qd.inrange_demo(image);
	//qd.pixel_statistic_demo(image);
	//qd.drawing_demo(image);
	//qd.random_drawing();
	//qd.polyline_drawing_demo();
	//qd.mouse_drawing_demo(image);
	//qd.norm_demo(image);
	//qd.resize_demo(image);
	//qd.flip_demo(image);
	//qd.rotate_demo(image);
	//qd.video_demo(image);
	//qd.histogram_demo(image);
	//qd.histogram_2d_demo(image);
	//qd.histogram_eq_demo(image);
	//qd.blur_demo(image);
	//qd.gaussian_blur_demo(image);
	qd.bifilter_demo(image);
	qd.face_detection_demo();
		
	waitKey(0);  //参数0为表示一直停止，1表示1毫秒
	destroyWindow("hello");    //销毁窗口
	return 0;
}
