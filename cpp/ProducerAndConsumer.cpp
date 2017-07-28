#include <iostream>
#include "ProducerAndConsumer.h"
#include "BreadContainer.h"
#include "BreadBasket.h"
#include "BreadBucket.h"
#include "Producer.h"
#include "Consumer.h"

using namespace std;

void producerAndConsumerTest() {
    cout << "begin" << endl;


    BreadContainer* breadContainer = new BreadBasket(10);
    breadContainer->init();

    Consumer* consumer1 = new Consumer(breadContainer);
    Producer* producer1 = new Producer(breadContainer);
    Consumer* consumer2 = new Consumer(breadContainer);
    Producer* producer2 = new Producer(breadContainer);
    Consumer* consumer3 = new Consumer(breadContainer);
    Producer* producer3 = new Producer(breadContainer);

    producer1->start();
    usleep(5);
    consumer1->start();

    producer2->start();
    usleep(5);
    consumer2->start();

    producer3->start();
    usleep(5);
    consumer3->start();


    usleep(60000000);
    cout << "end" << endl;
}

