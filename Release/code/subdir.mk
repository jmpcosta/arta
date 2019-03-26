################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/xml_data_handler.cpp \
../code/xml_error.cpp \
../code/xml_errorHandler.cpp \
../code/xml_hprocessor.cpp \
../code/xml_parser.cpp \
../code/xml_processor.cpp \
../code/xml_rprocessor.cpp \
../code/xml_string.cpp 

OBJS += \
./code/xml_data_handler.o \
./code/xml_error.o \
./code/xml_errorHandler.o \
./code/xml_hprocessor.o \
./code/xml_parser.o \
./code/xml_processor.o \
./code/xml_rprocessor.o \
./code/xml_string.o 

CPP_DEPS += \
./code/xml_data_handler.d \
./code/xml_error.d \
./code/xml_errorHandler.d \
./code/xml_hprocessor.d \
./code/xml_parser.d \
./code/xml_processor.d \
./code/xml_rprocessor.d \
./code/xml_string.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/joao/Software/xerces/src" -I"/home/joao/workspace/arta/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


