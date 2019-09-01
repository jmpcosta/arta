################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/arta_hproc_proc.cpp \
../code/main.cpp 

OBJS += \
./code/arta_hproc_proc.o \
./code/main.o 

CPP_DEPS += \
./code/arta_hproc_proc.d \
./code/main.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/home/joao/Software/xerces/src" -I"/home/joao/workspace/arta/code" -O0 -g3 -Wall -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


