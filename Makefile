# Derleyici ve bayraklar
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -I.

# Kaynak ve hedef dosyalar
SRCS      := main.cpp Kitap.cpp Stack.cpp Queue.cpp Tree.cpp Hash.cpp Auth.cpp
OBJS      := $(SRCS:.cpp=.o)
TARGET    := kitap_yonetim_sistemi.exe

.PHONY: all clean

# Varsayılan hedef
all: $(TARGET)

# Link aşaması
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Derleme kuralı (her .cpp -> .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Geçici dosyaları temizler
clean:
	rm -f $(OBJS) $(TARGET)
