################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/string/xml_string.cpp 

OBJS += \
./code/string/xml_string.o 

CPP_DEPS += \
./code/string/xml_string.d 


# Each subdirectory must supply rules for building sources it contributes
code/string/%.o: ../code/string/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/joao/Software/xerces/src" -I"/home/joao/workspace/arta/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


