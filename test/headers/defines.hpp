#ifndef defines
#include <fstream>
#include <string> 
#include <format>


#define FOPEN(stream, filename) std::ofstream stream; stream.open(filename,std::ios::app);

#define FCLOSE(stream) stream.close()

#define coutf std::cout <<std::format
#define fmt std::format
#define LOOP_MIN
#define defines
#endif // !defines

