################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/maker/xml_maker.cpp \
../code/maker/xml_makerDOM.cpp \
../code/maker/xml_makerWriter.cpp 

CPP_DEPS += \
./code/maker/xml_maker.d \
./code/maker/xml_makerDOM.d \
./code/maker/xml_makerWriter.d 

OBJS += \
./code/maker/xml_maker.o \
./code/maker/xml_makerDOM.o \
./code/maker/xml_makerWriter.o 


# Each subdirectory must supply rules for building sources it contributes
code/maker/%.o: ../code/maker/%.cpp code/maker/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"${XERCES_DIR}/src" -I"${ARTA_DIR}/code" -O3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-maker

clean-code-2f-maker:
	-$(RM) ./code/maker/xml_maker.d ./code/maker/xml_maker.o ./code/maker/xml_makerDOM.d ./code/maker/xml_makerDOM.o ./code/maker/xml_makerWriter.d ./code/maker/xml_makerWriter.o

.PHONY: clean-code-2f-maker

