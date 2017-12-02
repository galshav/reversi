################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/ComputerPlayerTest.cpp \
../test/gtest_main.cpp 

OBJS += \
./test/ComputerPlayerTest.o \
./test/gtest_main.o 

CPP_DEPS += \
./test/ComputerPlayerTest.d \
./test/gtest_main.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/gal/workspace/UnitTestsReversi/include" -I"/home/gal/workspace/UnitTestsReversi/gtest_src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


