TARGET := app
CXX := g++
CXXFLAGS := -Wall -std=c++14 -MMD

# 需要编译的源文件
SRCS := main.cpp game.cpp graph.cpp cgt.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 包含自动生成的依赖文件
-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: run clean