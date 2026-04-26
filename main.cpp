
#include <data.h>
#include <jsones.h>
#include <includes.h>
#include <myiterator.h>
#include <grafics.h>

using namespace std;
using json = nlohmann::json;


int main(){
setlocale(LC_ALL, "ru_RU.UTF-8");
//*iter::choose();

	try {
		GLFW glfw;
		Window w(500, 500,"hi");
		w.loop();
	}
	catch(const::std::runtime_error& e){
		std::cout << "except: " << e.what() << std::endl;
			return - 1;

	}


    return 0;
} 
