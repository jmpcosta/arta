################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/arta_creator.cpp \
../code/main.cpp 

OBJS += \
./code/arta_creator.o \
./code/main.o 

CPP_DEPS += \
./code/arta_creator.d \
./code/main.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/home/joao/workspace/arta/code" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


