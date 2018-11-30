VULKAN_SDK_PATH = /home/lzn/Desktop/graphics/1.1.85.0/x86_64
CFLAGS = -g -O0 -std=c++17 -I$(VULKAN_SDK_PATH)/include -I./stb -I./tinyobjloader -rdynamic
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

VulkanTest: 29_multisampling.cpp
	g++ $(CFLAGS) -o 29_multisampling 29_multisampling.cpp $(LDFLAGS)

.PHONY: test clean

test: 29_multisampling
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d ./29_multisampling

clean:
	rm -f 29_multisampling

