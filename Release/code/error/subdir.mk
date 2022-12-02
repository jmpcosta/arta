################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/error/xml_error.cpp \
../code/error/xml_errorHandler.cpp 

CPP_DEPS += \
./code/error/xml_error.d \
./code/error/xml_errorHandler.d 

OBJS += \
./code/error/xml_error.o \
./code/error/xml_errorHandler.o 


# Each subdirectory must supply rules for building sources it contributes
code/error/%.o: ../code/error/%.cpp code/error/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-error

clean-code-2f-error:
	-$(RM) ./code/error/xml_error.d ./code/error/xml_error.o ./code/error/xml_errorHandler.d ./code/error/xml_errorHandler.o

.PHONY: clean-code-2f-error

