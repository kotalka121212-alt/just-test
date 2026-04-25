#pragma once



//stl ->
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

//libs ->
#include <json.hpp>




//nn ->
#include "vector.h"
#include "matrix.h"
#include "activate.h"
#include "layer.h"
#include "network.h"


//boost ->

#include <boost/algorithm/string.hpp> //* для обработки строк
#include <boost/lexical_cast.hpp>   //* для конвертации
#include <boost/property_tree/json_parser.hpp> //* если нужен второй JSON парсер
#include <boost/random.hpp>//* нормальный рандом
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>





using namespace std;
using json = nlohmann::json;



