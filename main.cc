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

# include "joystick.hh"

# include <future>
# include <thread>
# include <chrono>

JoystickEvent event_handler(Joystick& joystick, JoystickEvent event)
{
  
  while (true)
  {            
    // Attempt to read an event from the joystick
    JoystickEvent event;

    if (joystick.read_event(&event)){
      
      if(joystick.ButtonAChanged(event)) {
	
	std::cout << "GOOOD A" << std::endl;			 
      }
      else if(joystick.ButtonBChanged(event)) {
	std::cout << "GOOOD B" << std::endl;			 
      }
      else if (joystick.isButton(event)){
	std::cout << "GOOOD  a button" << std::endl;
      }
      // printf("Button %u is %s\n",
      //  		 event.number,
      //  		 event.value == 0 ? "up" : "down");	  
    }
    
    /*  follow the same methode of value in QT monitor */
    /*  debug info to be added with debug  */
    // if (event.isButton())
    // 	{
    //
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
  Joystick joystick("/dev/input/js1");
  
  // Ensure that it was found and that we can use it
  if (!joystick.isFound())
    {
      std::cout << "No device found, please connect a joystick" << std::endl;
      exit(1);
    }

  JoystickEvent event;
  
  auto update_handler = [&](){			 
			 event_handler(joystick, event);
		       };
  

  auto joystick_event =  std::async(std::launch::async, update_handler);
  
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

  

