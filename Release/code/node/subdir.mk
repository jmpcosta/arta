################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/node/xml_node.cpp 

OBJS += \
./code/node/xml_node.o 

CPP_DEPS += \
./code/node/xml_node.d 


# Each subdirectory must supply rules for building sources it contributes
code/node/%.o: ../code/node/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


