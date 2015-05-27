#---------- env ----------
CXX=g++
CXXFLAGS=-std=gnu++11 -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -g -pipe -W -Wall -fPIC -fno-omit-frame-pointer
INCPATH=-I. -I/home/meihua/dy/src/glog/include -I/home/meihua/dy/src/se/include -I/home/meihua/dy/src/redis_proxy/output/include -I/home/meihua/dy/src/protobuf/include -I/home/meihua/dy/src/hiredis/include -I/home/meihua/dy/src/gflags/include -I/home/meihua/dy/src/seg_origin/output/include -I/home/meihua/dy/src/seg_origin/dep/include -I/home/meihua/dy/src/tmp/se/include -I/home/meihua/dy/src/mysql_proxy/output/include -I/home/meihua/dy/src/mysql-connector/include -I/home/meihua/dy/src/thrift/include -I/home/meihua/dy/src/json/output/include -I/home/meihua/dy/src/common_lib/output/include
LIBPATH=-Xlinker "-(" -ldl -lpthread -lm -lrt /home/meihua/dy/src/seg/lib/libseg_ext.a /home/meihua/dy/src/seg/lib/libsegment.a /home/meihua/dy/src/glog/lib/libglog.a /home/meihua/dy/src/redis_proxy/output/lib/libredis_proxy.a /home/meihua/dy/src/protobuf/lib/libprotoc.a /home/meihua/dy/src/protobuf/lib/libprotobuf.a /home/meihua/dy/src/protobuf/lib/libprotobuf-lite.a /home/meihua/dy/src/hiredis/lib/libhiredis.a /home/meihua/dy/src/gflags/lib/libgflags.a /home/meihua/dy/src/gflags/lib/libgflags_nothreads.a /home/meihua/dy/src/seg_origin/output/lib/libseg.a /home/meihua/dy/src/mysql_proxy/output/lib/libmysql_proxy.a /home/meihua/dy/src/mysql-connector/lib/libmysqlclient.a /home/meihua/dy/src/thrift/lib/libthriftnb.a /home/meihua/dy/src/thrift/lib/libthriftz.a /home/meihua/dy/src/thrift/lib/libthrift.a /home/meihua/dy/src/common_lib/output/lib/libcommon_lib.a -Xlinker "-)"


#---------- phony ----------
.PHONY:all
all:prepare \
demo \
libjson.a \


.PHONY:prepare
prepare:
	mkdir -p ./output/bin
	mkdir -p ./output/lib ./output/include

.PHONY:clean
clean:
	rm -rf /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/impl/json_bool.o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_nil.o /home/meihua/dy/src/json/impl/json_map.o /home/meihua/dy/src/json/impl/json_obj.o ./output


#---------- link ----------
demo:/home/meihua/dy/src/json/impl/json_array.o \
/home/meihua/dy/src/json/impl/json_bool.o \
/home/meihua/dy/src/json/impl/json_string.o \
/home/meihua/dy/src/json/demo/demo.o \
/home/meihua/dy/src/json/json.o \
/home/meihua/dy/src/json/impl/json_number.o \
/home/meihua/dy/src/json/impl/json_nil.o \
/home/meihua/dy/src/json/impl/json_map.o \
/home/meihua/dy/src/json/impl/json_obj.o \

	$(CXX) /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/impl/json_bool.o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_nil.o /home/meihua/dy/src/json/impl/json_map.o /home/meihua/dy/src/json/impl/json_obj.o $(LIBPATH) -o ./output/bin/demo

libjson.a:/home/meihua/dy/src/json/impl/json_string.o \
/home/meihua/dy/src/json/impl/json_bool.o \
/home/meihua/dy/src/json/impl/json_map.o \
/home/meihua/dy/src/json/impl/json_nil.o \
/home/meihua/dy/src/json/impl/json_array.o \
/home/meihua/dy/src/json/json.o \
/home/meihua/dy/src/json/impl/json_obj.o \
/home/meihua/dy/src/json/impl/json_number.o \

	ar crs ./output/lib/libjson.a /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/impl/json_bool.o /home/meihua/dy/src/json/impl/json_map.o /home/meihua/dy/src/json/impl/json_nil.o /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/impl/json_obj.o /home/meihua/dy/src/json/impl/json_number.o
	cp /home/meihua/dy/src/json/json.h /home/meihua/dy/src/json/json_obj.h /home/meihua/dy/src/json/exception.h /home/meihua/dy/src/json/define.h ./output/include/


#---------- obj ----------
/home/meihua/dy/src/json/impl/json_array.o: /home/meihua/dy/src/json/impl/json_array.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/impl/json_array.cpp
/home/meihua/dy/src/json/impl/json_bool.o: /home/meihua/dy/src/json/impl/json_bool.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_bool.o /home/meihua/dy/src/json/impl/json_bool.cpp
/home/meihua/dy/src/json/impl/json_string.o: /home/meihua/dy/src/json/impl/json_string.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h \
 /home/meihua/dy/src/common_lib/output/include/string_helper.h \
 /home/meihua/dy/src/json/impl/../exception.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/impl/json_string.cpp
/home/meihua/dy/src/json/demo/demo.o: /home/meihua/dy/src/json/demo/demo.cpp \
 /home/meihua/dy/src/json/demo/../json.h \
 /home/meihua/dy/src/json/demo/../json_obj.h \
 /home/meihua/dy/src/json/demo/../define.h \
 /home/meihua/dy/src/json/demo/../exception.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/demo/demo.cpp
/home/meihua/dy/src/json/json.o: /home/meihua/dy/src/json/json.cpp /home/meihua/dy/src/json/json.h \
 /home/meihua/dy/src/json/json_obj.h /home/meihua/dy/src/json/define.h \
 /home/meihua/dy/src/json/exception.h \
 /home/meihua/dy/src/common_lib/output/include/string_helper.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/json.cpp
/home/meihua/dy/src/json/impl/json_number.o: /home/meihua/dy/src/json/impl/json_number.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h \
 /home/meihua/dy/src/json/impl/../exception.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_number.cpp
/home/meihua/dy/src/json/impl/json_nil.o: /home/meihua/dy/src/json/impl/json_nil.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_nil.o /home/meihua/dy/src/json/impl/json_nil.cpp
/home/meihua/dy/src/json/impl/json_map.o: /home/meihua/dy/src/json/impl/json_map.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_map.o /home/meihua/dy/src/json/impl/json_map.cpp
/home/meihua/dy/src/json/impl/json_obj.o: /home/meihua/dy/src/json/impl/json_obj.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h \
 /home/meihua/dy/src/json/impl/../json.h \
 /home/meihua/dy/src/json/impl/../json_obj.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_obj.o /home/meihua/dy/src/json/impl/json_obj.cpp


