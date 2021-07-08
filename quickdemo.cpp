#include<quickopencv.h>
#include<opencv2/dnn.hpp>

using namespace cv;
using namespace std;


//图像色彩转换和展示图片，保存图片
void QuickDemo::colorSpace_Demo(Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	// H通道的范围：0-180，S,V:0-255,H,S表示颜色，V表示亮度，S还可以调整饱和度
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("灰度", gray);  //imshow只支持8位（256位 ）的或者是浮点数的显示，其他的多少有点问题，imread进来的肯定是8位的
	imwrite("E:/c_plus_project/hsv.png", hsv); 
	/*
	常用的有三个参数:
	1.保存的图片位置+名称+后缀，
	2.保存的内容
	3.const std::vector&类型的params，表示为特定格式保存的参数编码，它有默认值std::vector()，所以一般情况下不需要填写。
	如果更改的话，对于不同的图片格式，其对应的值不同功能不同，如下：
		对于JPEG格式的图片，这个参数表示从0-100的图片质量（CV_IMWRITE_JPEG_QUALITY）,默认值是95.
		对于PNG格式的图片，这个参数表示压缩级别（CV_IMWRITE_PNG_COMPRESSION）从0-9.较高的值意味着更小的尺寸和更长的压缩时间而默认值是3.
		对于PPM，PGM或PBM格式的图片，这个参数表示一个二进制格式标志（CV_IMWRITE_PXM_BINARY），取值为0或1，而默认值为1.
	*/
	imwrite("E:/c_plus_project/gray.png", gray);
}


//Mat对象常用操作
void QuickDemo::mat_creation_demo(Mat& image) {
	/*
	Mat的基本结构：头部+数据部分
	头部存储的是非像素值的其他属性信息（eg：长宽高，数据类型，通道...）
	赋值操作的实质：只是将指针志向的原来的数据，本质上还是指向同一个datablock
	克隆（src.clone()）或拷贝（复制，src.copyTo(m)）的时候才是将datablock复制过来使用
	*/
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);

	//创建空白图像
	Mat m3 = Mat::zeros(image.size(), image.type());
	
	Mat m4 = Mat::zeros(Size(512, 512), CV_8UC3);  //CV_8(位数)UC(unsigned char)1(单通道的)
	//m4 = 127;  //三通道时：这样赋值只会给第一个通道赋值为127
	//Mat m4 = Mat::zeros(Size(512, 512), CV_8UC3);
	//m4 = Scalar(127, 127, 127);  //给对应的通道赋值
	//imshow("m4", m4);
	//std::cout << m4 << std::endl;
	//std::cout << "width:" << m4.cols << "heght:" << m4.rows << "channels:" << m4.channels() << std::endl;
	
	Mat m5 = Mat::ones(Size(8, 8), CV_8UC3);  //一定要注意这里初始化的ones只有第一位为1，其他位都是0.所以尽量使用初始化为单通道的
	std::cout << m5 << std::endl;

	// 赋值操作
	//Mat m6 = m4;

	// 克隆操作
	//Mat m6 = m4.clone();

	// 拷贝操作
	Mat m6;
	m4.copyTo(m6);
	m6 = Scalar(0, 0, 255);
	imshow("img4", m4);

	
	// 快速创建一个卷积核
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
}


//普通方法与指针实现图像加法操作
void QuickDemo::pixel_visit_demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = image.at<uchar>(row, col);  //获取当前像素值
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);  //获取得到三个值 int-Vec3i,float-Vec3f
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}*/
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = *current_row;  //获取当前像素值
				*current_row++ = 255 - pv;
			}
			if (dims == 3) {//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);  //获取得到三个值 int-Vec3i,float-Vec3f
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("像素反转显示", image);
}


//实现图像算数操作
void QuickDemo::operators_demo(Mat& image) {
	/*Mat dst;
	//dst = image + Scalar(50, 50, 50);
	//dst = image - Scalar(50, 50, 50);
	//dst = image / Scalar(2, 2, 2);
	//dst = image * Scalar(2, 2, 2);//这并不是真正的乘法操作
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);
	multiply(image, m, dst); //如果相乘之后大于255，就会自动截断到255
	imshow("加法操作", dst);*/

	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	/*//这个方法就是与add等效的
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);  //获取得到三个值 int-Vec3i,float-Vec3f
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0]+p2[0]);  //saturate_cast<类型>（数字），该方法的作用就是对数字做范围限制，使数字在类型所属范围内
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1]+p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2]+p2[2]);
			
		}
	}*/
	add(image, m, dst);// 减法为subtract，除法为divide
	imshow("乘法操作", dst);
	
}

//窗口调整亮度
/*窗口调整亮度
类外面定义变量不符合面向对象性质，比较low的操作
Mat src, dst, m;
int lightness = 50;  
static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	add(src, m, dst);
	imshow("亮度调整", dst);
}


void QuickDemo::tracking_bar_demo(Mat &image) {
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	dst = Mat::zeros(image.size(), image.type()); // 初始化过了这里就不需要再写Mat了，不然会有bug
	m = Mat::zeros(image.size(), image.type());
	src = image;
	int max_value = 100;
	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);  //trackbar名称，窗口名称，trackbar实时改变的值，最大值，触发时间函数(回调函数)
	on_track(50, 0);
}*/
static void on_lightness(int b, void* userdata) {// 同一个窗口调整亮度和对比度
	Mat image = *((Mat*)userdata);  // ((Mat*)userdata)Mat类型的指针，指针变数据前面加*
	Mat dst = Mat::zeros(image.size(), image.type()); 
	Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("亮度与对比度调整", dst);
}

static void on_contrast(int b, void* userdata) {// 同一个窗口调整亮度和对比度
	Mat image = *((Mat*)userdata);  // ((Mat*)userdata)Mat类型的指针，指针变数据前面加*
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(b, b, b);
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("亮度与对比度调整", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {// 同一个窗口调整亮度和对比度
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));  //trackbar名称，窗口名称，trackbar实时改变的值，最大值，触发时间函数(回调函数)
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));  //trackbar名称，窗口名称，trackbar实时改变的值，最大值，触发时间函数(回调函数)

	on_lightness(50, &image);  // 传指针
}


//键盘与操作
void QuickDemo::key_demo(Mat& image) { 
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);  //最常用的就是waitKey(1)
		if (c == 27) {  //esc退出
			break;
		}
		if (c == 49) {
			std::cout << "you enter key # 1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50) {
			std::cout << "you enter key # 2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {
			std::cout << "you enter key # 3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("键盘响应", dst);
	}
}


//自带颜色表实现炫酷操作
void QuickDemo::color_style_demo(Mat& image) {
	int colormap[] = { COLORMAP_AUTUMN, COLORMAP_BONE, COLORMAP_JET, COLORMAP_WINTER,COLORMAP_RAINBOW,COLORMAP_OCEAN,COLORMAP_SUMMER, COLORMAP_SPRING,COLORMAP_COOL,COLORMAP_PINK,COLORMAP_HOT,COLORMAP_PARULA,COLORMAP_MAGMA,COLORMAP_INFERNO,COLORMAP_PLASMA,COLORMAP_VIRIDIS,COLORMAP_CIVIDIS,COLORMAP_TWILIGHT,COLORMAP_TWILIGHT_SHIFTED };
	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(2000);
		if (c == 27) {
			break;
		}
		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		imshow("颜色风格", dst);
	}
}


//图像的位运算
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);  //rectangle（图片，rect（x，y，w，h），Scalar（图片颜色），-1（小于0的都是填充矩形，大于0的表示绘制矩形），LINE_8（常用的线条样式），
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	bitwise_and(m1, m2, dst);
	imshow("像素与操作", dst);

	bitwise_or(m1, m2, dst);
	imshow("像素或操作", dst);

	bitwise_not(image, dst);  //Mat dst = ~image;
	imshow("像素取反操作", dst);

	bitwise_xor(m1, m2, dst);
	imshow("像素异或操作", dst);
}


//图像通道变化
void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);  //分离通达
	imshow("蓝色", mv[0]);
	imshow("绿色", mv[1]);
	imshow("红色", mv[2]);

	Mat dst;
	//mv[1] = 0;
	//mv[2] = 0;
	//merge(mv, dst);
	//imshow("蓝色", dst);

	mv[0] = 0;
	//mv[2] = 0;
	merge(mv, dst);  //合并通道
	imshow("绿色", dst);

	int from_to[] = { 0,2,1,1,2,0 };//通道交换的顺序
	mixChannels(&image, 1, &dst, 1, from_to, 3);//对调通道顺序
	imshow("通道混合", dst);
}


//图像色彩空间转换
void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35,43,46), Scalar(77, 255,255), mask);  //mask的获取
	imshow("mask", mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);  //赋值为红色
	bitwise_not(mask, mask);
	imshow("mask", mask);
	image.copyTo(redback, mask);  //将不为0的像素进行拷贝
	imshow("roi区域", redback);
}


//像素值统计
void QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;
	Point minLoc, maxLoc;
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		std::cout << "No. channels:" << i << " min value:" << minv << " max value:" << maxv << std::endl;
		std::cout << "No. channels:" << i << " minLoc:" << minLoc << " maxLoc:" << maxLoc << std::endl;
	}
	
	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	//mean.at<double>(0, 0);
	std::cout << "means:" << mean << std::endl;
	std::cout << " stddev:" << stddev << std::endl;
}


//图像几何形状的绘制
void QuickDemo::drawing_demo(Mat& image) {
	Rect rect;
	rect.x = 200;
	rect.y = 200;
	rect.width = 300;
	rect.height = 300;

	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);  //画矩形
	circle(bg, Point(500, 500), 15, Scalar(255, 0, 0), -1, 8, 0);
	//Mat dst;
	//addWeighted(image, 0.7, bg, 0.3, 0, dst);
	//imshow("绘制演示", dst);
	line(bg, Point(200, 200), Point(500, 500), Scalar(0, 255, 0), 2, 8, 0);  //8可以换成line_AA这个是反锯齿，很平滑的
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 90.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);  //椭圆
	imshow("绘制演示", bg);
}


//随机数随机颜色的生成
void QuickDemo::random_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);  //产生随机数的，12345是随机数的种子，默认的种子是计算机的时间
	while (true)
	{
		int c = waitKey(10);
		if (c == 27) {
			break;
		}
		int x1 = rng.uniform(0, w);//rng.uniform产生一个同一分布的随机数
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvas = Scalar(0, 0, 0);//重置背景色
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);
		imshow("绘制演示", canvas);
	}
}


//绘制和填充多边形
void QuickDemo::polyline_drawing_demo() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);
	//点变成集合
	std::vector<Point>pts;  //没有初始化所以不能直接赋值,只能用push_back
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	
	//fillPoly(canvas, pts, Scalar(255, 0, 255), 8, 0);  //填充多边形
	//polylines(canvas, pts, true, Scalar(0, 0, 255), 2, LINE_AA, 0);  //这个函数不能使用thickness<0来实现填充效果
	std::vector<std::vector<Point>> contours;
	contours.push_back(pts);
	drawContours(canvas, contours, -1, Scalar(255, 0, 0), 2);  // 可以绘制多个多边形,contourIdx=0->1个,-1->全部,thickness<0来实现填充效果
	imshow("多边形绘制", canvas);
}


//
Point sp(-1, -1); //全局变量以记录状态
Point ep(-1, -1);
Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {  //鼠标绘制矩形的方法
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {  // 点击鼠标左键
		sp.x = x;
		sp.y = y;
		std::cout << "start point:" << sp << std::endl;
	}
	else if(event == EVENT_LBUTTONUP){  //抬起鼠标左键。抬起的时候就是结束的位置
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		//右下角坐标不能超出图片范围，否则要报错，可以做出限定
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			imshow("鼠标绘制", image);
			temp.copyTo(image);//放在roi前面，这样roi里面就不会有边框了
			imshow("ROI区域", image(box));//提取ROI区域
			//为一下次绘制做好准备
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if(event==EVENT_MOUSEMOVE){
		if (sp.x > 0 && sp.y > 0) {  //没有绘制起点的时候鼠标移动不产生效果
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);
			}
		}
	}
}

//鼠标操作与相应
void QuickDemo::mouse_drawing_demo(Mat &image) {
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
	imshow("鼠标绘制", image);
	temp = image.clone();
}


//像素归一化
void QuickDemo::norm_demo(Mat& image) {
	Mat dst;
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);  //转为浮点数
	std::cout << image.type() << std::endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);  // 归一化
	std::cout << dst.type() << std::endl;
	imshow("图像像素归一化", dst);
}


//图像放缩与差值
void QuickDemo::resize_demo(Mat& image) {
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("缩小", zoomin);
	resize(image, zoomout, Size(w *1.2, h *1.2), 0, 0, INTER_LINEAR);
	imshow("放大", zoomout);
}


//图像翻转
void QuickDemo::flip_demo(Mat& image) {
	Mat dst;
	//flip(image, dst, 0);//上下翻转
	//flip(image, dst, 1);//左右翻转
	flip(image, dst, -1);//旋转180度
	imshow("图像翻转", dst);
}


//图像旋转
void QuickDemo::rotate_demo(Mat& image) {
	Mat dst, M;
	double w = image.cols;
	double h = image.rows;
	M = getRotationMatrix2D(Point2f(w / 2., h / 2.), 45, 1.0);  //参数，1-原来图像的中心位置，2-旋转的角度，3-图像的放缩大小
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	double nw = cos * w + sin * h;
	double nh = sin * w + cos * h;
	M.at<double>(0, 2) += nw / 2. - w / 2.;
	M.at<double>(1, 2) += nh / 2. - h / 2.;
	warpAffine(image, dst, M, Size(nw,nh), INTER_LINEAR,0,Scalar(255,0,0));  //填充的背景设为白色
	imshow("旋转显示", dst);
}


//打开视频  //视频清晰度等级：SD-标清（<720p），HD-高清（720p-1080p），UHD-超清/蓝光(1080p以上的)
//opencv专门用于视频处理的，不会有声音，想处理声音需要使用ffmpeg。保存的视频不能超过2G。编码方式都是调用ffmpeg来实现的
void QuickDemo::video_demo(Mat& image) {
	VideoCapture capture("C:/Users/Administrator/Desktop/output.mp4");
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH); //视频宽
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);  //视频高
	int count = capture.get(CAP_PROP_FRAME_COUNT);  //视频总帧数
	double fps = capture.get(CAP_PROP_FPS);
	//set属性要在支持的相机上才能起作用
	std::cout << "frame_width " << frame_width << "frame_height " << frame_height << "count " << count << "fps " << fps << std::endl;
	VideoWriter writer("C:/Users/Administrator/Desktop/output1.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);//编码方式是一定要写的，常用的就是fourcc
	Mat frame;
	while (true)
	{
		capture.read(frame);
		//flip(frame, frame, 1);
		if (frame.empty()) {
			break;
		}
		imshow("frame", frame);
		//colorSpace_Demo(frame);
		writer.write(frame);
		int c = waitKey(10);
		if (c == 27) {
			break;
		}
	}
	capture.release();
	writer.release();
}


//直方图  图像平移旋转之后，直方图都不变，应用在阈值分割，颜色图像检索，特征提取，反向投影，视频分析，模式识别当中
void QuickDemo::histogram_demo(Mat& image) {
	std::vector<Mat> bgr_plane;  //三通道分离
	split(image, bgr_plane);
	// 定义参数变量
	const int channels[1] = { 0 };
	//总共256个灰度级别
	//计算颜色直方图需要将颜色空间划分为若干小的颜色区间，即直方图的bin，
	//通过计算颜色在每个小区间内的像素得到颜色直方图，bin越多，直方图对颜色的分辨率越强，但增加了计算机的负担。
	const int bins[1] = { 256 };  
	float hranges[2] = { 0,255 }; //每个通道的取值范围
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// 计算Blue，Green，Red通道的直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	//归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//绘制直方图曲线
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


// 二维直方图
void QuickDemo::histogram_2d_demo(Mat& image) {
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV); //转成hsv
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins,sbins };
	float h_range[] = { 0,180 };
	float s_range[] = { 0,256 };
	const float* hs_ranges[] = { h_range,s_range };
	int hs_channels[] = { 0, 1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);  //找到最大值
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);// 空白图像的作用是将直方图归一化后的值填充到上面
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++) {
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1), Scalar::all(intensity), -1);
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
}


//直方图均衡化，只能对单通道的图像操作,如果想对彩色图片直方图均衡化，可以转为HSV格式对V通道进行直方图均衡化，再merge回HSV再转为rgb，经常用于图像增强
void QuickDemo::histogram_eq_demo(Mat& image) {
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("灰度图像", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("直方图均衡化", dst);

}

//均值卷积操作
void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1)); //point为默认的中心位置
	//blur(image, dst, Size(15, 1), Point(-1, -1)); //水平方向卷积
	//blur(image, dst, Size(1, 15), Point(-1, -1)); //垂直方向卷积
	imshow("卷积模糊", dst);
}


//高斯模糊
void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15); //这里的Size只能是正奇数，偶数违反了高斯中心化的原则，会报错
	//sigma是由size换算来的，填了size之后，sigma填啥都没用，因此老手都只使用sigma不使用size

	imshow("高斯模糊", dst);
}


//高斯双边（空间，rgb）模糊,保存大体信息，模糊细节信息
void QuickDemo::bifilter_demo(Mat& image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	namedWindow("双边模糊", WINDOW_FREERATIO);
	imshow("双边模糊", dst);
}


//

void QuickDemo::face_detection_demo() {
	std::string root_dir = "D:/C_opencv/opencv-4.5.1/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	VideoCapture capture("C:/Users/Administrator/Desktop/output.mp4");
	Mat frame;
	while (true) {
		capture.read(frame);
		if (frame.empty()) {
			break;
		}

		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false); //scalefactor默认是1.0，为0-255，如果是0.0384，就是归一化到0-1
		net.setInput(blob);  //NCHW
		Mat probs = net.forward(); //
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5) {
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1, y1, x2-x1, y2-y1);
				rectangle(frame, box, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		imshow("人脸检测演示", frame);
		
		int c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
}