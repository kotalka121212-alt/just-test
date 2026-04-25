#include <data.h>
#include <jsones.h>
#include <includes.h>
#include <myiterator.h>



using namespace std;
using json = nlohmann::json;



int main(){


setlocale(LC_ALL, "ru_RU.UTF-8");

//*iter::choose();

    NeuralNetwork net(0.5);
    net.addLayer(2, 4);
    net.addLayer(4, 1);

    Vector inputs[] = {
        Vector({0.0, 0.0}),
        Vector({0.0, 1.0}),
        Vector({1.0, 0.0}),
        Vector({1.0, 1.0})
    };
    Vector targets[] = {
        Vector({0.0}),
        Vector({1.0}),
        Vector({1.0}),
        Vector({0.0})
    };

    // Train
    for (int epoch = 0; epoch < 20000; ++epoch) {
        for (int i = 0; i < 4; ++i) {
            net.train(inputs[i], targets[i]);
        }
    }

    // Test
    for (int i = 0; i < 4; ++i) {
        Vector out = net.predict(inputs[i]);
        inputs[i].print();
        std::cout << " -> ";
        out.print();
    }

    return 0;
} 
