// banner.cpp
#include <iostream>
#include "../include/banner.hpp"
#include <unistd.h>

void showBanner() {
    std::cout << "\033[1;35m";
    std::cout << R"(                                                                         
                                                                                                                                                            
                                .: ..^:.!..:^..^                                
                            :^:::5!..7~.Y..?^~!7!J:.::                          
                        ::^~^??!:~BG?PGP#YPGYYGY5:^?!^:::.                      
                     .:^::~JGBGG&#BGG55555PPGB#&JG&P77!!:.:.:.                  
                    .:^!JBGY7:.PPYJ?7P#&&#J!7JYPJ .^?55J5PY?~.  ..              
                   :^~JG5!.   :G?7!~B@@@@G   :7?G.    .~JGGY777!:               
                 .^!P&5^      :P!~~^G@@@@@B^.^~!G.      .:!Y5YJ7^:.             
                 :75Y?.        J7^^::7PBBP!::^^J7       :~JJ^::.                
                 ^::^~^.        !7^:........:^?~      .~?57^..                  
               .  ....:....      .~~~^^::^^~~^     .^!77^.  ..                  
                        .^7?!7~^:....^^^^^:...:~~!7Y?:   ..                     
                            ...!7:~?Y~^?!^~Y?:~Y?.  .:.                         
                               .   ^   ^   .^   ..                              
                                       .                                        
                                           
    )" << "\n\033[0m";
}

void showWelcomeInfo() {
    // Get date and time
    time_t now = time(0);
    char* dt = ctime(&now);

    // Get hostname
    char hostname[255];
    gethostname(hostname, 255);

    // Print system info in styled form
    std::cout << "\033[1;34m";
    std::cout << "Date & Time : " << dt;
    std::cout << "Hostname    : " << hostname << std::endl;

    // Welcome message
    std::cout << "\033[1;32m"  // Green
              << "Welcome to Lash: Your visionary shell.\n"
              << "See your commands clearly.\n\n";
    std::cout << "\033[0m"; // Reset
}