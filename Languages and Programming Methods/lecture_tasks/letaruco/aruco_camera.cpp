#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera!" << endl;
        return -1;
    }

    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_100);

    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();

    namedWindow("ArUco Marker Detection", WINDOW_NORMAL);
    
    cout << "Press ESC to exit..." << endl;
    
    while (true) {
        Mat frame;
        cap >> frame;
        
        if (frame.empty()) {
            cerr << "Error: Could not capture frame!" << endl;
            break;
        }

        vector<int> ids;
        vector<vector<Point2f>> corners;

        aruco::detectMarkers(frame, dictionary, corners, ids, detectorParams);

        if (!ids.empty()) {
            aruco::drawDetectedMarkers(frame, corners, ids);

            cout << "Detected markers: " << ids.size() << endl;
            
            for (size_t i = 0; i < ids.size(); i++) {
                Point2f center(0, 0);
                for (size_t j = 0; j < corners[i].size(); j++) {
                    center.x += corners[i][j].x;
                    center.y += corners[i][j].y;
                }
                center.x /= corners[i].size();
                center.y /= corners[i].size();
                
                cout << "Marker ID: " << ids[i] << endl;
                cout << "Center position: (" << center.x << ", " << center.y << ")" << endl;

                for (size_t j = 0; j < corners[i].size(); j++) {
                    cout << "  Corner " << j << ": (" 
                         << corners[i][j].x << ", " << corners[i][j].y << ")" << endl;
                }
            }
        }
        imshow("ArUco Marker Detection", frame);
        
        if (waitKey(10) == 27) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    
    return 0;
}