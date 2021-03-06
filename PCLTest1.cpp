// PCLTest1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <Windows.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/integral_image_normal.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl\features\normal_3d_omp.h>

using namespace pcl;
using namespace std;

int main()
{
	LARGE_INTEGER nfreq, nst, nend;//Timer parameters.
	PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);//Create point cloud pointer.
	string reloadfile = "no";//If need to input new file.
	string exit = "no";//If exit this program;
	string filename = "";
	string prefile = "";
	string dirstr = "F:\\PCLTest\\data\\";
	string fullfile = dirstr;
	pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::Normal> ne;
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());//Create a null kdtree object.
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);

	do
	{
		cout << "Need to load/reload point cloud fle? (Y or N)\a" << endl;
		cin >> reloadfile;
		while(reloadfile == "YES" || reloadfile == "yes" || reloadfile == "Y" || reloadfile == "y")
		{
			//Input the name of point cloud file.
			filename = "";
			cout << "Plese move your point could file into F:\\PCLTest\\data\\" << endl;
			cout << "Please input data file name: " << endl;
			cin >> filename;
			if (prefile == filename)
			{
				cout << "Your current input file is the same as previous one." << endl;
				break;
			}
			fullfile = "";
			fullfile = dirstr + filename;
			//Load point cloud file.
			QueryPerformanceFrequency(&nfreq);
			QueryPerformanceCounter(&nst);
			int f_error = pcl::io::loadPLYFile(fullfile, *cloud);
			QueryPerformanceCounter(&nend);
			cout << "Loading ply file costs " << (nend.QuadPart - nst.QuadPart)*1.0 / nfreq.QuadPart << " seconds." << endl;
			if (f_error == -1)
			{
				cout << "Couldn't find file named tyre1.ply." << endl;
				system("PAUSE");
				return -2;
			}

			//Estimating normal
			ne.setNumberOfThreads(4);
			ne.setInputCloud(cloud);
			
			//Transfer kdtree object to normal estimation object.
			ne.setSearchMethod(tree);
			//Output data set.
			prefile = reloadfile;
			reloadfile = "";
		};

		//Searching neighbors in 3 cm radius.
		cout << "Please input searching radius(m): " << endl;
		double radius = 0.1;//Default radius is 10 cm.
		while (!(cin >> radius))
		{
			cout << "The input variable is not an interge, please type again." << endl;
		};
		ne.setRadiusSearch(radius);
		//Compute eigenvalue.
		QueryPerformanceCounter(&nst);
		ne.compute(*cloud_normals);
		QueryPerformanceCounter(&nend);
		cout << "Computing eigenvalue costs " << (nend.QuadPart - nst.QuadPart)*1.0 / nfreq.QuadPart << " seconds." << endl;
		// cloud_normals->points.size () should have the same size with input cloud_downsampled->points.size ()
		//Normal Visulization
		pcl::visualization::PCLVisualizer viewer("PCL Viewer");
		viewer.setBackgroundColor(0.0, 0.0, 0.0);
		viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, cloud_normals);

		while (!viewer.wasStopped())
		{
			viewer.spinOnce();
		}

		
		cout << "Do you want to exit this program? (Y or N)" << endl;
		cin >> exit;
	} while (exit == "no" || exit =="NO" || exit =="N" || exit =="n");
	/*if (loadPCDFile<PointXYZ>("E:\\pcl1.8\\rabbit.pcd", *cloud) == -1) //Load pcd file, if unsucessful, return -1.
	{
		PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //The pcd file doesn't exist, print error info and return error code -2.
		return -2;
	}
	cout<<"Loaded "<< cloud->width * cloud->height<<" data points from tyre1.ply with the following fields:"<< endl;
	//for (size_t i = 0; i < cloud->points.size (); ++i) //Show all points.
	for(size_t i=0;i<5;++i)//For easy review, just output 5 points here.
	{
		cout<<"    "<<cloud->points[i].x<<" "<<cloud->points[i].y<<" "<<cloud->points[i].z<<endl;
	}
	//getchar();*/
	system("PAUSE");
	return 0;
}

