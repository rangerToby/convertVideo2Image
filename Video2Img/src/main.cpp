#include <iostream>

#include "cv.h"
#include "opencv2/opencv.hpp"

//for mkdir
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
using namespace cv;

//************************************
// Method:    string_replace
// FullName:  string_replace
// Access:    public 
// Returns:   void
// Qualifier: 把字符串的strsrc替换成strdst
// Parameter: std::string & strBig
// Parameter: const std::string & strsrc
// Parameter: const std::string & strdst
//************************************
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }
}

//************************************
// Method:    GetFileOrURLShortName
// FullName:  GetFileOrURLShortName
// Access:    public 
// Returns:   std::string
// Qualifier: 获取路径或URL的文件名（包括后缀，如 C:\Test\abc.xyz --> abc.xyz）
// Parameter: std::string strFullName
//************************************
std::string GetPathOrURLShortName(std::string strFullName)
{
    if (strFullName.empty())
    {
        return "";
    }

    // string_replace(strFullName, "/", "\\");

    std::string::size_type iPos = strFullName.find_last_of('/') + 1;

    return strFullName.substr(iPos, strFullName.length() - iPos);
}

//************************************
// Method:    GetFileOrURLShortName
// FullName:  GetFileOrURLShortName
// Access:    public 
// Returns:   std::string
// Qualifier: 获取路径或URL的文件名（包括后缀，如 C:\Test\abc.xyz --> abc.xyz）
// Parameter: std::string strFullName
//************************************
std::string removeExtension(std::string fileName)
{
    if (fileName.empty())
    {
        return "";
    }

    // string_replace(strFullName, "/", "\\");

    std::string::size_type iPos = fileName.find_last_of('.');

    return fileName.substr(0, iPos);
}


int main(int argc, char** argv)
{
    // video read
    CvCapture *capture = cvCreateFileCapture(argv[1]);
    IplImage *frame;

   	string inputString = argv[1];
   	string noExtensionFileName = removeExtension(GetPathOrURLShortName(inputString));

    char outputDirName[100];
    sprintf( outputDirName, "output/%s", noExtensionFileName.c_str());
    int isCreate = mkdir(outputDirName,S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    if( !isCreate )
   		printf("create path:%s\n",outputDirName);
    else
   		printf("create path failed! error code : %s \n",isCreate,outputDirName);

   	// cout<<noExtension<<endl;

    int imgIndex(0);
    int interval_c = 0;
    int frame_count = 0;
    while(1)
    {	

        frame = cvQueryFrame(capture);
        if ( !frame )
        {
            break;
        }

        if (!(interval_c%1)) // change the number of interval
        {

        char imageSaveName[100];
        sprintf( imageSaveName, "%s/%08d.jpg", outputDirName, frame_count );
        // printf("%s\n",imageSaveName );
        cvSaveImage( imageSaveName, frame );
        // printf("writing %d frame\n", imgIndex);
        imgIndex++;
        }
        else 
        printf("reading\n");
        interval_c++;
        frame_count++;
    }

    cout << "total frames: " << --imgIndex << endl;
    cvDestroyWindow( "VideoImage" );
    cvReleaseCapture( &capture );
    cvReleaseImage( &frame );
}
