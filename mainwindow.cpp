#include <iostream>
#include <iterator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/bgsegm.hpp"
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

String getSimiliarImageFile(String originalfile);
String getRandomImageFile();
int GetRandomNumber(const int Min, const int Max);
String getRandomImage();
QImage Mat2QImage(cv::Mat const& src);
Mat QImage2Mat(QImage const& src);
double getPSNR(const Mat& I1, const Mat& I2);
Scalar getMSSIM( const Mat& i1, const Mat& i2);
bool MatchTest(Mat img1, Mat img2);
vector<double> MassMatchTest();
int sizeValidation(Mat img1,Mat img2);
double MassSizeTest();

Mat image1, image2; // these are the variables that carries images that will be compared
bool samecar;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Compares Car1 and Car2 images
 **/
void MainWindow::on_randomValid_btn_clicked()
{

    if(image1.empty() ||image2.empty()){
        QMessageBox msgBox;
        msgBox.setText("Warning");
        msgBox.setInformativeText("You should select 2 car images");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
    else{
       if (MatchTest(image1,image2))
       {
           ui->result_label->setText(QString("Result: These are same cars "));
           samecar = true;
       }
       else
       {
           ui->result_label->setText(QString("Result: These are NOT same cars "));
           samecar = false;
       }
    }



}

void MainWindow::on_sizeValid_btn_clicked()
{
    if(samecar)
    {
        int result = sizeValidation(image1,image2);
        if (result == 1)
        {
            ui->result_label->setText(QString("Result: Car 1 image is bigger "));
        }
        else if(result == 2)
        {
             ui->result_label->setText(QString("Result: Car 2 image is bigger "));
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Warning");
        msgBox.setInformativeText("You should select 2 same car images");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
}

/*
 * Gets random images from folder and puts  themin QLabels
 **/
void MainWindow::on_GetRandomImage_btn_clicked()
{
    String randomFile = getRandomImageFile();
    String randomFile2 = getRandomImageFile();
    Mat randomImg = imread(randomFile);
    Mat randomImg2 = imread(randomFile2);
    if(randomImg.empty() || randomImg2.empty()){
        QMessageBox msgBox;
        msgBox.setText("Warning");
        msgBox.setInformativeText("There is no valid file name");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
    else{

        image1 = randomImg;
        image2 = randomImg2;
        int w = randomImg.cols;
        int h = randomImg.rows;
        int w2 = randomImg.cols;
        int h2 = randomImg.rows;
        QImage img =Mat2QImage(randomImg);
        QPixmap p =  QPixmap::fromImage(img);
        QImage img2 =Mat2QImage(randomImg2);
        QPixmap p2 =  QPixmap::fromImage(img2);
        ui->image1_label->setPixmap(p.scaled(w,h,Qt::KeepAspectRatioByExpanding));
        ui->image2_label->setPixmap(p2.scaled(w2,h2,Qt::KeepAspectRatioByExpanding));

    }
}


/*
 * Gets images that has label name from folder and puts them in QLabels
 **/
void MainWindow::on_GetSameImage_btn_3_clicked()
{
    String randomFile = getRandomImageFile();
    String sameCarFile = getSimiliarImageFile(randomFile);

    Mat sameCarImg1 = imread(randomFile);
    Mat sameCarImg2 = imread(sameCarFile);

    if(sameCarImg1.empty() || sameCarImg2.empty()){
        QMessageBox msgBox;
        msgBox.setText("Warning");
        msgBox.setInformativeText("There is no valid file name");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
    else{
        image1 = sameCarImg1;
        image2 = sameCarImg2;
        int w = sameCarImg1.cols;
        int h = sameCarImg1.rows;
        int w2 = sameCarImg2.cols;
        int h2 = sameCarImg2.rows;
        QImage img =Mat2QImage(sameCarImg1);
        QPixmap p =  QPixmap::fromImage(img);

        QImage img2 =Mat2QImage(sameCarImg2);
        QPixmap p2 =  QPixmap::fromImage(img2);
        ui->image1_label->setPixmap(p.scaled(w,h,Qt::KeepAspectRatioByExpanding));
        ui->image2_label->setPixmap(p2.scaled(w2,h2,Qt::KeepAspectRatioByExpanding));
        samecar = true;
    }
}

/*
 *
 *Button for All Files Match Test
 **/
void MainWindow::on_matchtest4all_btn_2_clicked()
{
   vector<double> result = MassMatchTest();
   QString result4pos = QString::number(result[0]);
   QString result4neg = QString::number(result[1]);
   ui->result_label->setText("Result for positive matches: " + result4pos + "\nResult for negative matches: " + result4neg);
}

void MainWindow::on_sizeTest4All_btn_clicked()
{
    double sizeResult = MassSizeTest();
    QString result2show = QString::number(sizeResult);
    ui->result_label->setText("Result for Size Validation: " + result2show);
}
/*
 * Larger car has more common pixels than smaller car.
 * When we get difference between images larger car will have more remaining pixels than smaller car
 * psnr between larger car and difference matrix will be bigger than psnr between smaller car and difference matrix
 * So, it gets absdiff of two images and calculates psnr between smallcar-diff and bigcar-diff
 * According to results returns which one is bigger
 * */
int sizeValidation(Mat img1,Mat img2)
{
    cv::resize( img2, img2, img1.size(), 0, 0, INTER_LINEAR );
    Mat frame1,frame2;
    cvtColor(img1,frame1,CV_BGR2GRAY);
    cvtColor(img2,frame2,CV_BGR2GRAY);

   /* Rect largest1 = contourfind(frame1,frame2);
   // Rect largest2 = contourfind(img2);

    rectangle(img1, largest1,  Scalar(255,0,255),2, 8,0);
    //rectangle(img2, largest2,  Scalar(0,255,0),1, 8,0);
    imshow( "1", img1 );
    //imshow( "2", img2 );*/

    Mat s1,s2,s3;

    absdiff(img1, img2, s1);
   /* absdiff(img1,s1,s2);
    absdiff(img2,s1,s3);*/
    cv::erode(s1, s1, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));
    blur( s1, s1, Size(3,3) );


    double psnr = getPSNR(s1,img1);
    double psnr2 = getPSNR(s1,img2);
    /**Scalar ssim1 = getMSSIM(s2,img1);
    Scalar ssim2 = getMSSIM(s3,img2);
    double avgssim1 = (ssim1[0] + ssim1[1] + ssim1[2]) / 3.0;
    double avgssim2 = (ssim2[0] + ssim2[1] + ssim2[2]) / 3.0;

    cout << "mssim : " << abs(avgssim1) << "--" << abs(avgssim2) << endl;
    cout << "psnr : " <<psnr << "--" << psnr2 << endl;
    cout << "-------------------"<<endl;*/

    if (psnr2 > psnr){

        return 2;
    }
    else if (psnr > psnr2)
    {
        return 1;
    }
}


/*
 * Gets a random image file from pairs folder
 **/
String getRandomImageFile()
{

    vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "./pairs"; // again we are using the Opencv's embedded "String" class
    String randomfilename;
    int random,total;

    glob(folder, filenames); // get whole file names in folder

    total = filenames.size();
    random = GetRandomNumber(0,total);  // gets random number between total filename count and 1

    randomfilename = filenames[random];

    return randomfilename;
}



/*
 * It takes originalfile name as input and find other match of this image in folder
 * Returns similar image file's path
 **/
String getSimiliarImageFile(String originalfile)
{
    String similiarfile,tmp_originalfile;

    size_t indexofsplitter;
    indexofsplitter = originalfile.find_first_of("_");
    tmp_originalfile = originalfile.substr(0,indexofsplitter);

   // cout << originalfile.c_str() << endl;


    vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "./pairs"; // again we are using the Opencv's embedded "String" class

    int totalfilecount;
    vector<int> similiarfileindex;

    glob(folder, filenames); // gets whole file names in folder

    // it will scan all files and extract files that matches with original file name till "_" char.
    totalfilecount = filenames.size();
    for (int i =0; i<totalfilecount; i++)
    {
        String tmpfilename;
        indexofsplitter = filenames[i].find_first_of("_");
        tmpfilename = filenames[i].substr(0,indexofsplitter);


        if(tmp_originalfile == tmpfilename)
        {
            similiarfileindex.push_back(i);
        }

    }

    // get avoid from taking same original file name again
    int countOfsimiliars = similiarfileindex.size();
    for(int j = 0; j < countOfsimiliars; j++)
    {
        if(filenames[similiarfileindex[j]] != originalfile){
            similiarfile = filenames[similiarfileindex[j]];
        }
    }
    return similiarfile;
}


/*
 * Calculates psnr and mssim values from images
 * applies defined thresholds to psnr and mssim values
 * returns bool according to similiarity between img1 and img2
 **/
bool MatchTest(Mat img1, Mat img2)
{
    Scalar imgs;
    double psnrThres,mmsimThres;

    cv::resize( img2, img2, img1.size(), 0, 0, INTER_LINEAR );
    double psnr = getPSNR(img1,img2);

    imgs = getMSSIM(img1,img2);
    double avgMMSIM = (imgs[0] + imgs[1] + imgs[2])/3.0;

    psnrThres = 11.5;
    mmsimThres = 0.2;

    if(psnr == 0) // if psnr is 0 it's absoultely the same car.
    {
        return true;
    }

    if(avgMMSIM > mmsimThres && psnr > psnrThres)// above of these thresholds means these are same car
    {
        // These cars are same
        return true;
    }
    else{
        // These cars are not same
        return false;
    }

}


/*
 * test all images for positive matches and negative matches
 * positive match ex. 51497560_0.png - 51497560_6.png..
 * negative match ex. 51497560_0.png - 197966074_0.png..
 */
vector<double> MassMatchTest()
{
    vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "./pairs"; // again we are using the Opencv's embedded "String" class
    size_t indexofsplitter;

    glob(folder, filenames); // gets whole file names in folder

    int totalfilecount, goodvalidofpositives,goodvalidofnegatives;
    double normalization4pos;
    double normalization4neg;

    goodvalidofpositives = 0;
    goodvalidofnegatives = 0;


    totalfilecount = filenames.size();
    normalization4pos = totalfilecount/2.0; // There are 37 positive matches.
    normalization4neg =((totalfilecount-4) * (double)totalfilecount); // which is 74*70 = 5180 -- There are 5180 negative matches.

    Mat frame1,frame2;

    for (int i =0; i<totalfilecount; i++)
    {
        String tmpfilename;
        indexofsplitter = filenames[i].find_first_of("_"); // get file names till '_' char
        tmpfilename = filenames[i].substr(0,indexofsplitter);
        for (int j =0; j<totalfilecount; j++)
        {
            String tmpfilename2;

            tmpfilename2 = filenames[j].substr(0,indexofsplitter);

            frame1 = imread(filenames[i]);
            frame2 = imread(filenames[j]);

            if (tmpfilename == tmpfilename2)
            {

                if(j > i)// we dont want match exactly the same images.
                {

                    if(MatchTest(frame1,frame2) == true)
                    {
                        //we already know that frame1 and frame2 are same cars,
                        // so getting true from match test shows we classified correctly
                        goodvalidofpositives++;
                    }

                }
            }
            else{
                // This else is covering tests of images that names are not matching. Only will applied in type 2
                if(MatchTest(frame1,frame2) == false) // it will give false when cars are not same
                {
                    //we already know that frame1 and frame2 are different cars,
                    // so getting false from match test shows we classified correctly
                    goodvalidofnegatives++;
                }
            }
        }
    }
    vector<double> result;
    result.push_back((goodvalidofpositives/normalization4pos)*100.0);
    result.push_back((goodvalidofnegatives/normalization4neg)*100.0);

    return result;
}

/**
 * @brief Finds same images with diffferent index numbers than compares them according to sizeValidation function
 *
 * @return a double that consists ratio of accuracy
 */
double MassSizeTest()
{
    vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "./pairs"; // again we are using the Opencv's embedded "String" class
    size_t indexofsplitter;

    glob(folder, filenames); // gets whole file names in folder

    int totalfilecount, goodvalidofsizes;
    double normalization;

    goodvalidofsizes = 0;


    totalfilecount = filenames.size();
    normalization = totalfilecount/2.0; // There are 37 size matches.

    Mat frame1,frame2;

    for (int i =0; i<totalfilecount; i++)
    {
        String tmpfilename;
        indexofsplitter = filenames[i].find_first_of("_"); // get file names till '_' char
        tmpfilename = filenames[i].substr(0,indexofsplitter);
        String tmpfileindex = filenames[i].substr(indexofsplitter+1,filenames[i].size());

        int index1;
        sscanf(tmpfileindex.c_str(), "%d", &index1);

        for (int j =0; j<totalfilecount; j++)
        {
            String tmpfilename2;
            String tmpfileindex2;
            tmpfilename2 = filenames[j].substr(0,indexofsplitter);
            tmpfileindex2 = filenames[j].substr(indexofsplitter+1,filenames[j].size());

            int index2;
            sscanf(tmpfileindex2.c_str(), "%d", &index2);

            frame1 = imread(filenames[i]);
            frame2 = imread(filenames[j]);

            if (tmpfilename == tmpfilename2)
            {

                    if(index1>index2)// frame1 var is bigger than frame2 car
                    {

                        if(sizeValidation(frame1,frame2) == 1) // if frame1 car is bigger thane frame2 car, count it
                        {
                            // size comparson matches with true value

                            goodvalidofsizes++;
                        }
                    }

            }

        }
    }
    double result;

    /*cout << goodvalidofsizes << endl;*/
    result = ((goodvalidofsizes/(double)normalization)*100.0);
   // cout << result << endl;
    return result;
}


double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);         // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double  mse =sse /(double)(I1.channels() * I1.total());
        double psnr = 10.0*log10((255*255)/mse);
        return psnr;
    }
}

Scalar getMSSIM( const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d     = CV_32F;

    Mat I1, I2;
    i1.convertTo(I1, d);           // cannot calculate on one byte large values
    i2.convertTo(I2, d);

    Mat I2_2   = I2.mul(I2);        // I2^2
    Mat I1_2   = I1.mul(I1);        // I1^2
    Mat I1_I2  = I1.mul(I2);        // I1 * I2

    /***********************PRELIMINARY COMPUTING ******************************/

    Mat mu1, mu2;   //
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);

    Mat mu1_2   =   mu1.mul(mu1);
    Mat mu2_2   =   mu2.mul(mu2);
    Mat mu1_mu2 =   mu1.mul(mu2);

    Mat sigma1_2, sigma2_2, sigma12;

    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;

    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;

    ///////////////////////////////// FORMULA ////////////////////////////////
    Mat t1, t2, t3;

    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

    Scalar mssim = mean( ssim_map ); // mssim = average of ssim map
    return mssim;
}

QImage Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp; // make the same cv::Mat
    cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result,CV_BGR2RGB);
    return result;
}

int GetRandomNumber(const int Min, const int Max)
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    return ((qrand() % ((Max + 1) - Min)) + Min);
}


