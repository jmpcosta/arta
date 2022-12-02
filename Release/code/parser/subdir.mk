################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/parser/xml_cprocessor.cpp \
../code/parser/xml_data_handler.cpp \
../code/parser/xml_hprocessor.cpp \
../code/parser/xml_parser.cpp \
../code/parser/xml_processor.cpp \
../code/parser/xml_rprocessor.cpp 

CPP_DEPS += \
./code/parser/xml_cprocessor.d \
./code/parser/xml_data_handler.d \
./code/parser/xml_hprocessor.d \
./code/parser/xml_parser.d \
./code/parser/xml_processor.d \
./code/parser/xml_rprocessor.d 

OBJS += \
./code/parser/xml_cprocessor.o \
./code/parser/xml_data_handler.o \
./code/parser/xml_hprocessor.o \
./code/parser/xml_parser.o \
./code/parser/xml_processor.o \
./code/parser/xml_rprocessor.o 


# Each subdirectory must supply rules for building sources it contributes
code/parser/%.o: ../code/parser/%.cpp code/parser/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-parser

clean-code-2f-parser:
	-$(RM) ./code/parser/xml_cprocessor.d ./code/parser/xml_cprocessor.o ./code/parser/xml_data_handler.d ./code/parser/xml_data_handler.o ./code/parser/xml_hprocessor.d ./code/parser/xml_hprocessor.o ./code/parser/xml_parser.d ./code/parser/xml_parser.o ./code/parser/xml_processor.d ./code/parser/xml_processor.o ./code/parser/xml_rprocessor.d ./code/parser/xml_rprocessor.o

.PHONY: clean-code-2f-parser

