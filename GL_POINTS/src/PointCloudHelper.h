#pragma once
#include <string>
#include <vector>





class PointCloudHelper
{
public:

	static void loadAndExportToLas(const std::string& point_cloud_path, const std::string& output_name);

	static void loadAndExportToLas(const std::vector<std::string>& point_cloud_paths, const std::string& output_name);

};

