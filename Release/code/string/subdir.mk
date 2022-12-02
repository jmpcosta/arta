################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/string/xml_string.cpp 

CPP_DEPS += \
./code/string/xml_string.d 

OBJS += \
./code/string/xml_string.o 


# Each subdirectory must supply rules for building sources it contributes
code/string/%.o: ../code/string/%.cpp code/string/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-string

clean-code-2f-string:
	-$(RM) ./code/string/xml_string.d ./code/string/xml_string.o

.PHONY: clean-code-2f-string

