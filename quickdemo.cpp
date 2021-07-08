#include<quickopencv.h>
#include<opencv2/dnn.hpp>

using namespace cv;
using namespace std;


//ͼ��ɫ��ת����չʾͼƬ������ͼƬ
void QuickDemo::colorSpace_Demo(Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	// Hͨ���ķ�Χ��0-180��S,V:0-255,H,S��ʾ��ɫ��V��ʾ���ȣ�S�����Ե������Ͷ�
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);  //imshowֻ֧��8λ��256λ ���Ļ����Ǹ���������ʾ�������Ķ����е����⣬imread�����Ŀ϶���8λ��
	imwrite("E:/c_plus_project/hsv.png", hsv); 
	/*
	���õ�����������:
	1.�����ͼƬλ��+����+��׺��
	2.���������
	3.const std::vector&���͵�params����ʾΪ�ض���ʽ����Ĳ������룬����Ĭ��ֵstd::vector()������һ������²���Ҫ��д��
	������ĵĻ������ڲ�ͬ��ͼƬ��ʽ�����Ӧ��ֵ��ͬ���ܲ�ͬ�����£�
		����JPEG��ʽ��ͼƬ�����������ʾ��0-100��ͼƬ������CV_IMWRITE_JPEG_QUALITY��,Ĭ��ֵ��95.
		����PNG��ʽ��ͼƬ�����������ʾѹ������CV_IMWRITE_PNG_COMPRESSION����0-9.�ϸߵ�ֵ��ζ�Ÿ�С�ĳߴ�͸�����ѹ��ʱ���Ĭ��ֵ��3.
		����PPM��PGM��PBM��ʽ��ͼƬ�����������ʾһ�������Ƹ�ʽ��־��CV_IMWRITE_PXM_BINARY����ȡֵΪ0��1����Ĭ��ֵΪ1.
	*/
	imwrite("E:/c_plus_project/gray.png", gray);
}


//Mat�����ò���
void QuickDemo::mat_creation_demo(Mat& image) {
	/*
	Mat�Ļ����ṹ��ͷ��+���ݲ���
	ͷ���洢���Ƿ�����ֵ������������Ϣ��eg������ߣ��������ͣ�ͨ��...��
	��ֵ������ʵ�ʣ�ֻ�ǽ�ָ��־���ԭ�������ݣ������ϻ���ָ��ͬһ��datablock
	��¡��src.clone()���򿽱������ƣ�src.copyTo(m)����ʱ����ǽ�datablock���ƹ���ʹ��
	*/
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);

	//�����հ�ͼ��
	Mat m3 = Mat::zeros(image.size(), image.type());
	
	Mat m4 = Mat::zeros(Size(512, 512), CV_8UC3);  //CV_8(λ��)UC(unsigned char)1(��ͨ����)
	//m4 = 127;  //��ͨ��ʱ��������ֵֻ�����һ��ͨ����ֵΪ127
	//Mat m4 = Mat::zeros(Size(512, 512), CV_8UC3);
	//m4 = Scalar(127, 127, 127);  //����Ӧ��ͨ����ֵ
	//imshow("m4", m4);
	//std::cout << m4 << std::endl;
	//std::cout << "width:" << m4.cols << "heght:" << m4.rows << "channels:" << m4.channels() << std::endl;
	
	Mat m5 = Mat::ones(Size(8, 8), CV_8UC3);  //һ��Ҫע�������ʼ����onesֻ�е�һλΪ1������λ����0.���Ծ���ʹ�ó�ʼ��Ϊ��ͨ����
	std::cout << m5 << std::endl;

	// ��ֵ����
	//Mat m6 = m4;

	// ��¡����
	//Mat m6 = m4.clone();

	// ��������
	Mat m6;
	m4.copyTo(m6);
	m6 = Scalar(0, 0, 255);
	imshow("img4", m4);

	
	// ���ٴ���һ�������
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
}


//��ͨ������ָ��ʵ��ͼ��ӷ�����
void QuickDemo::pixel_visit_demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = image.at<uchar>(row, col);  //��ȡ��ǰ����ֵ
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {//��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);  //��ȡ�õ�����ֵ int-Vec3i,float-Vec3f
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}*/
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = *current_row;  //��ȡ��ǰ����ֵ
				*current_row++ = 255 - pv;
			}
			if (dims == 3) {//��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);  //��ȡ�õ�����ֵ int-Vec3i,float-Vec3f
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("���ط�ת��ʾ", image);
}


//ʵ��ͼ����������
void QuickDemo::operators_demo(Mat& image) {
	/*Mat dst;
	//dst = image + Scalar(50, 50, 50);
	//dst = image - Scalar(50, 50, 50);
	//dst = image / Scalar(2, 2, 2);
	//dst = image * Scalar(2, 2, 2);//�Ⲣ���������ĳ˷�����
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);
	multiply(image, m, dst); //������֮�����255���ͻ��Զ��ضϵ�255
	imshow("�ӷ�����", dst);*/

	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	/*//�������������add��Ч��
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);  //��ȡ�õ�����ֵ int-Vec3i,float-Vec3f
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0]+p2[0]);  //saturate_cast<����>�����֣����÷��������þ��Ƕ���������Χ���ƣ�ʹ����������������Χ��
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1]+p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2]+p2[2]);
			
		}
	}*/
	add(image, m, dst);// ����Ϊsubtract������Ϊdivide
	imshow("�˷�����", dst);
	
}

//���ڵ�������
/*���ڵ�������
�����涨���������������������ʣ��Ƚ�low�Ĳ���
Mat src, dst, m;
int lightness = 50;  
static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	add(src, m, dst);
	imshow("���ȵ���", dst);
}


void QuickDemo::tracking_bar_demo(Mat &image) {
	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
	dst = Mat::zeros(image.size(), image.type()); // ��ʼ����������Ͳ���Ҫ��дMat�ˣ���Ȼ����bug
	m = Mat::zeros(image.size(), image.type());
	src = image;
	int max_value = 100;
	createTrackbar("Value Bar:", "���ȵ���", &lightness, max_value, on_track);  //trackbar���ƣ��������ƣ�trackbarʵʱ�ı��ֵ�����ֵ������ʱ�亯��(�ص�����)
	on_track(50, 0);
}*/
static void on_lightness(int b, void* userdata) {// ͬһ�����ڵ������ȺͶԱȶ�
	Mat image = *((Mat*)userdata);  // ((Mat*)userdata)Mat���͵�ָ�룬ָ�������ǰ���*
	Mat dst = Mat::zeros(image.size(), image.type()); 
	Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("������Աȶȵ���", dst);
}

static void on_contrast(int b, void* userdata) {// ͬһ�����ڵ������ȺͶԱȶ�
	Mat image = *((Mat*)userdata);  // ((Mat*)userdata)Mat���͵�ָ�룬ָ�������ǰ���*
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	//m = Scalar(b, b, b);
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("������Աȶȵ���", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {// ͬһ�����ڵ������ȺͶԱȶ�
	namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));  //trackbar���ƣ��������ƣ�trackbarʵʱ�ı��ֵ�����ֵ������ʱ�亯��(�ص�����)
	createTrackbar("Contrast Bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));  //trackbar���ƣ��������ƣ�trackbarʵʱ�ı��ֵ�����ֵ������ʱ�亯��(�ص�����)

	on_lightness(50, &image);  // ��ָ��
}


//���������
void QuickDemo::key_demo(Mat& image) { 
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);  //��õľ���waitKey(1)
		if (c == 27) {  //esc�˳�
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
		imshow("������Ӧ", dst);
	}
}


//�Դ���ɫ��ʵ���ſ����
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
		imshow("��ɫ���", dst);
	}
}


//ͼ���λ����
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);  //rectangle��ͼƬ��rect��x��y��w��h����Scalar��ͼƬ��ɫ����-1��С��0�Ķ��������Σ�����0�ı�ʾ���ƾ��Σ���LINE_8�����õ�������ʽ����
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	bitwise_and(m1, m2, dst);
	imshow("���������", dst);

	bitwise_or(m1, m2, dst);
	imshow("���ػ����", dst);

	bitwise_not(image, dst);  //Mat dst = ~image;
	imshow("����ȡ������", dst);

	bitwise_xor(m1, m2, dst);
	imshow("����������", dst);
}


//ͼ��ͨ���仯
void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);  //����ͨ��
	imshow("��ɫ", mv[0]);
	imshow("��ɫ", mv[1]);
	imshow("��ɫ", mv[2]);

	Mat dst;
	//mv[1] = 0;
	//mv[2] = 0;
	//merge(mv, dst);
	//imshow("��ɫ", dst);

	mv[0] = 0;
	//mv[2] = 0;
	merge(mv, dst);  //�ϲ�ͨ��
	imshow("��ɫ", dst);

	int from_to[] = { 0,2,1,1,2,0 };//ͨ��������˳��
	mixChannels(&image, 1, &dst, 1, from_to, 3);//�Ե�ͨ��˳��
	imshow("ͨ�����", dst);
}


//ͼ��ɫ�ʿռ�ת��
void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35,43,46), Scalar(77, 255,255), mask);  //mask�Ļ�ȡ
	imshow("mask", mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);  //��ֵΪ��ɫ
	bitwise_not(mask, mask);
	imshow("mask", mask);
	image.copyTo(redback, mask);  //����Ϊ0�����ؽ��п���
	imshow("roi����", redback);
}


//����ֵͳ��
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


//ͼ�񼸺���״�Ļ���
void QuickDemo::drawing_demo(Mat& image) {
	Rect rect;
	rect.x = 200;
	rect.y = 200;
	rect.width = 300;
	rect.height = 300;

	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);  //������
	circle(bg, Point(500, 500), 15, Scalar(255, 0, 0), -1, 8, 0);
	//Mat dst;
	//addWeighted(image, 0.7, bg, 0.3, 0, dst);
	//imshow("������ʾ", dst);
	line(bg, Point(200, 200), Point(500, 500), Scalar(0, 255, 0), 2, 8, 0);  //8���Ի���line_AA����Ƿ���ݣ���ƽ����
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 90.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);  //��Բ
	imshow("������ʾ", bg);
}


//����������ɫ������
void QuickDemo::random_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);  //����������ģ�12345������������ӣ�Ĭ�ϵ������Ǽ������ʱ��
	while (true)
	{
		int c = waitKey(10);
		if (c == 27) {
			break;
		}
		int x1 = rng.uniform(0, w);//rng.uniform����һ��ͬһ�ֲ��������
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvas = Scalar(0, 0, 0);//���ñ���ɫ
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);
		imshow("������ʾ", canvas);
	}
}


//���ƺ��������
void QuickDemo::polyline_drawing_demo() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);
	//���ɼ���
	std::vector<Point>pts;  //û�г�ʼ�����Բ���ֱ�Ӹ�ֵ,ֻ����push_back
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	
	//fillPoly(canvas, pts, Scalar(255, 0, 255), 8, 0);  //�������
	//polylines(canvas, pts, true, Scalar(0, 0, 255), 2, LINE_AA, 0);  //�����������ʹ��thickness<0��ʵ�����Ч��
	std::vector<std::vector<Point>> contours;
	contours.push_back(pts);
	drawContours(canvas, contours, -1, Scalar(255, 0, 0), 2);  // ���Ի��ƶ�������,contourIdx=0->1��,-1->ȫ��,thickness<0��ʵ�����Ч��
	imshow("����λ���", canvas);
}


//
Point sp(-1, -1); //ȫ�ֱ����Լ�¼״̬
Point ep(-1, -1);
Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {  //�����ƾ��εķ���
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {  // ���������
		sp.x = x;
		sp.y = y;
		std::cout << "start point:" << sp << std::endl;
	}
	else if(event == EVENT_LBUTTONUP){  //̧����������̧���ʱ����ǽ�����λ��
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		//���½����겻�ܳ���ͼƬ��Χ������Ҫ�������������޶�
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			imshow("������", image);
			temp.copyTo(image);//����roiǰ�棬����roi����Ͳ����б߿���
			imshow("ROI����", image(box));//��ȡROI����
			//Ϊһ�´λ�������׼��
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if(event==EVENT_MOUSEMOVE){
		if (sp.x > 0 && sp.y > 0) {  //û�л�������ʱ������ƶ�������Ч��
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("������", image);
			}
		}
	}
}

//����������Ӧ
void QuickDemo::mouse_drawing_demo(Mat &image) {
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������", on_draw, (void*)(&image));
	imshow("������", image);
	temp = image.clone();
}


//���ع�һ��
void QuickDemo::norm_demo(Mat& image) {
	Mat dst;
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);  //תΪ������
	std::cout << image.type() << std::endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);  // ��һ��
	std::cout << dst.type() << std::endl;
	imshow("ͼ�����ع�һ��", dst);
}


//ͼ��������ֵ
void QuickDemo::resize_demo(Mat& image) {
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("��С", zoomin);
	resize(image, zoomout, Size(w *1.2, h *1.2), 0, 0, INTER_LINEAR);
	imshow("�Ŵ�", zoomout);
}


//ͼ��ת
void QuickDemo::flip_demo(Mat& image) {
	Mat dst;
	//flip(image, dst, 0);//���·�ת
	//flip(image, dst, 1);//���ҷ�ת
	flip(image, dst, -1);//��ת180��
	imshow("ͼ��ת", dst);
}


//ͼ����ת
void QuickDemo::rotate_demo(Mat& image) {
	Mat dst, M;
	double w = image.cols;
	double h = image.rows;
	M = getRotationMatrix2D(Point2f(w / 2., h / 2.), 45, 1.0);  //������1-ԭ��ͼ�������λ�ã�2-��ת�ĽǶȣ�3-ͼ��ķ�����С
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	double nw = cos * w + sin * h;
	double nh = sin * w + cos * h;
	M.at<double>(0, 2) += nw / 2. - w / 2.;
	M.at<double>(1, 2) += nh / 2. - h / 2.;
	warpAffine(image, dst, M, Size(nw,nh), INTER_LINEAR,0,Scalar(255,0,0));  //���ı�����Ϊ��ɫ
	imshow("��ת��ʾ", dst);
}


//����Ƶ  //��Ƶ�����ȵȼ���SD-���壨<720p����HD-���壨720p-1080p����UHD-����/����(1080p���ϵ�)
//opencvר��������Ƶ����ģ��������������봦��������Ҫʹ��ffmpeg���������Ƶ���ܳ���2G�����뷽ʽ���ǵ���ffmpeg��ʵ�ֵ�
void QuickDemo::video_demo(Mat& image) {
	VideoCapture capture("C:/Users/Administrator/Desktop/output.mp4");
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH); //��Ƶ��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);  //��Ƶ��
	int count = capture.get(CAP_PROP_FRAME_COUNT);  //��Ƶ��֡��
	double fps = capture.get(CAP_PROP_FPS);
	//set����Ҫ��֧�ֵ�����ϲ���������
	std::cout << "frame_width " << frame_width << "frame_height " << frame_height << "count " << count << "fps " << fps << std::endl;
	VideoWriter writer("C:/Users/Administrator/Desktop/output1.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);//���뷽ʽ��һ��Ҫд�ģ����õľ���fourcc
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


//ֱ��ͼ  ͼ��ƽ����ת֮��ֱ��ͼ�����䣬Ӧ������ֵ�ָ��ɫͼ�������������ȡ������ͶӰ����Ƶ������ģʽʶ����
void QuickDemo::histogram_demo(Mat& image) {
	std::vector<Mat> bgr_plane;  //��ͨ������
	split(image, bgr_plane);
	// �����������
	const int channels[1] = { 0 };
	//�ܹ�256���Ҷȼ���
	//������ɫֱ��ͼ��Ҫ����ɫ�ռ仮��Ϊ����С����ɫ���䣬��ֱ��ͼ��bin��
	//ͨ��������ɫ��ÿ��С�����ڵ����صõ���ɫֱ��ͼ��binԽ�ֱ࣬��ͼ����ɫ�ķֱ���Խǿ���������˼�����ĸ�����
	const int bins[1] = { 256 };  
	float hranges[2] = { 0,255 }; //ÿ��ͨ����ȡֵ��Χ
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// ����Blue��Green��Redͨ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	//��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	//��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


// ��άֱ��ͼ
void QuickDemo::histogram_2d_demo(Mat& image) {
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV); //ת��hsv
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins,sbins };
	float h_range[] = { 0,180 };
	float s_range[] = { 0,256 };
	const float* hs_ranges[] = { h_range,s_range };
	int hs_channels[] = { 0, 1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);  //�ҵ����ֵ
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);// �հ�ͼ��������ǽ�ֱ��ͼ��һ�����ֵ��䵽����
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


//ֱ��ͼ���⻯��ֻ�ܶԵ�ͨ����ͼ�����,�����Բ�ɫͼƬֱ��ͼ���⻯������תΪHSV��ʽ��Vͨ������ֱ��ͼ���⻯����merge��HSV��תΪrgb����������ͼ����ǿ
void QuickDemo::histogram_eq_demo(Mat& image) {
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ��", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯", dst);

}

//��ֵ�������
void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1)); //pointΪĬ�ϵ�����λ��
	//blur(image, dst, Size(15, 1), Point(-1, -1)); //ˮƽ������
	//blur(image, dst, Size(1, 15), Point(-1, -1)); //��ֱ������
	imshow("���ģ��", dst);
}


//��˹ģ��
void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15); //�����Sizeֻ������������ż��Υ���˸�˹���Ļ���ԭ�򣬻ᱨ��
	//sigma����size�������ģ�����size֮��sigma��ɶ��û�ã�������ֶ�ֻʹ��sigma��ʹ��size

	imshow("��˹ģ��", dst);
}


//��˹˫�ߣ��ռ䣬rgb��ģ��,���������Ϣ��ģ��ϸ����Ϣ
void QuickDemo::bifilter_demo(Mat& image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	namedWindow("˫��ģ��", WINDOW_FREERATIO);
	imshow("˫��ģ��", dst);
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

		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false); //scalefactorĬ����1.0��Ϊ0-255�������0.0384�����ǹ�һ����0-1
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
		imshow("���������ʾ", frame);
		
		int c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
}