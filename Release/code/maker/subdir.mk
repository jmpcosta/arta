################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/maker/xml_maker.cpp 

OBJS += \
./code/maker/xml_maker.o 

CPP_DEPS += \
./code/maker/xml_maker.d 


# Each subdirectory must supply rules for building sources it contributes
code/maker/%.o: ../code/maker/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/joao/Software/xerces/src" -I"/home/joao/workspace/arta/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


