// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright Drew Noakes 2013-2016

#include "joystick.hh"

#include <unistd.h>
# include <future>
# include <thread>
# include <chrono>

/*BLOCKING Function, to be executed async*/
JoystickEvent get_event(Joystick& joystick)
{
  
  while (true)
  {    
        
    // Attempt to sample an event from the joystick
    JoystickEvent event;

    joystick.read_event(&event);

    /*  follow the same methode of value in QT monitor */
    /*  debug info to be added with debug  */
      // if (event.isButton())
      // 	{
      // 	  printf("Button %u is %s\n",
      // 		 event.number,
      // 		 event.value == 0 ? "up" : "down");
      // 	}
      // else if (event.isAxis())
      // 	{
      // 	  printf("Axis %u is at position %d\n", event.number, event.value);
      // 	}
  }
}

int main(int argc, char** argv)
{
  
  // Create an instance of Joystick
  Joystick joystick("/dev/input/js0");
  
  // Ensure that it was found and that we can use it
  if (!joystick.isFound())
    {
      std::cout << "No device found." << std::endl;
      exit(1);
    }

  JoystickEvent event;
  
  auto event_handler = [&](){
			 
			 event = get_event(joystick);
			 if(joystick.ButtonAChanged()) {
			   
			   std::cout << "GOOOD A" << std::endl;			 
			 }
			 else if(joystick.ButtonBChanged()) {
			   std::cout << "GOOOD B" << std::endl;			 
			 }
		       };
  

  auto joystick_event =  std::async(std::launch::async, event_handler);
  
  auto test =
    std::async(std::launch::async,
	       [](){
		 
		 while(true)
		   {
		     std::this_thread::sleep_for(std::chrono::seconds(1));
		     std::cout<< "testing in async mode..." << std::endl;
		   }
	       }
	       );
  
  joystick_event.get();
  test.get();
}

  

