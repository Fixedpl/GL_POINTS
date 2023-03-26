#include "PointCloudHelper.h"

#include <fstream>

#include "lasreader.hpp"
#include "laswriter.hpp"




void PointCloudHelper::loadAndExportToLas(const std::string& point_cloud_path, const std::string& output_name)
{
	LASreadOpener* las_read_opener = new LASreadOpener();
	LASreader* las_reader = las_read_opener->open(point_cloud_path.c_str());

	std::string output_file_name = output_name + ".las";

	std::ofstream output_file(output_file_name);
	LASwriteOpener* las_write_opener = new LASwriteOpener();
	las_write_opener->set_file_name(output_file_name.c_str());
	las_write_opener->set_format(1);
	LASwriter* las_writer_las = las_write_opener->open(&las_reader->header);

	while (las_reader->read_point()) {
		LASpoint& point = las_reader->point;
		las_writer_las->write_point(&las_reader->point);
	}

	output_file.close();
}

void PointCloudHelper::loadAndExportToLas(const std::vector<std::string>& point_cloud_paths, const std::string& output_name)
{
	std::string output_file_name = output_name + ".las";
	std::ofstream output_file(output_file_name);
	

	LASreadOpener* las_read_opener = new LASreadOpener();

	LASreader* las_reader = las_read_opener->open(point_cloud_paths[0].c_str());
	LASheader header = las_reader->header;
	las_reader->close();

	uint32_t sum_points = 0;

	for (auto& path : point_cloud_paths) {
		LASreader* las_reader_it = las_read_opener->open(path.c_str());
		LASheader cur_header = las_reader_it->header;
		sum_points += cur_header.number_of_point_records;
		las_reader_it->close();
	}

	header.number_of_point_records = sum_points;

	LASwriteOpener* las_write_opener = new LASwriteOpener();
	las_write_opener->set_file_name(output_file_name.c_str());
	las_write_opener->set_format(1);
	LASwriter* las_writer_las = las_write_opener->open(&header);

	for (auto& path : point_cloud_paths) {
		LASreader* las_reader_it = las_read_opener->open(path.c_str());
		
		while (las_reader_it->read_point()) {
			LASpoint& point = las_reader_it->point;
			las_writer_las->write_point(&las_reader_it->point);
		}

		las_reader_it->close();
	}
	

	

	output_file.close();
}
