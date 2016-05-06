#include "SampleClient.h"
#include <iostream>
using namespace std;

int main() {
	SampleClient client;
	client.start("http://192.168.2.93:8000");
	while(true);
	return 0;
}
