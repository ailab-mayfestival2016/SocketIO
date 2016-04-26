#include "SampleClient.h"
#include <iostream>
using namespace std;

int main() {
	SampleClient client;
	client.start("http://localhost:8000");
	while(true);
	return 0;
}
