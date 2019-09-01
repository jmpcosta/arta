################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/error/xml_error.cpp \
../code/error/xml_errorHandler.cpp 

OBJS += \
./code/error/xml_error.o \
./code/error/xml_errorHandler.o 

CPP_DEPS += \
./code/error/xml_error.d \
./code/error/xml_errorHandler.d 


# Each subdirectory must supply rules for building sources it contributes
code/error/%.o: ../code/error/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DOSAPI_TRACING -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O0 -g3 -Wall -c -fmessage-length=0 -v -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


