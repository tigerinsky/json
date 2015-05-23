#---------- env ----------
CXX=g++
CXXFLAGS=-std=gnu++11 -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -g -pipe -W -Wall -fPIC -fno-omit-frame-pointer
INCPATH=-I. -I/home/meihua/dy/src/json/../glog/include -I/home/meihua/dy/src/json/../se/include -I/home/meihua/dy/src/json/../redis_proxy/output/include -I/home/meihua/dy/src/json/../protobuf/include -I/home/meihua/dy/src/json/../hiredis/include -I/home/meihua/dy/src/json/../gflags/include -I/home/meihua/dy/src/json/../seg_origin/output/include -I/home/meihua/dy/src/json/../seg_origin/dep/include -I/home/meihua/dy/src/json/../tmp/se/include -I/home/meihua/dy/src/json/../mysql_proxy/output/include -I/home/meihua/dy/src/json/../mysql-connector/include -I/home/meihua/dy/src/json/../thrift/include -I/home/meihua/dy/src/json/../json/output/include -I/home/meihua/dy/src/json/../common_lib/output/include
LIBPATH=-Xlinker "-(" -ldl -lpthread -lm -lrt /home/meihua/dy/src/json/../seg/lib/libseg_ext.a /home/meihua/dy/src/json/../seg/lib/libsegment.a /home/meihua/dy/src/json/../glog/lib/libglog.a /home/meihua/dy/src/json/../redis_proxy/output/lib/libredis_proxy.a /home/meihua/dy/src/json/../protobuf/lib/libprotoc.a /home/meihua/dy/src/json/../protobuf/lib/libprotobuf.a /home/meihua/dy/src/json/../protobuf/lib/libprotobuf-lite.a /home/meihua/dy/src/json/../hiredis/lib/libhiredis.a /home/meihua/dy/src/json/../gflags/lib/libgflags.a /home/meihua/dy/src/json/../gflags/lib/libgflags_nothreads.a /home/meihua/dy/src/json/../seg_origin/output/lib/libseg.a /home/meihua/dy/src/json/../mysql_proxy/output/lib/libmysql_proxy.a /home/meihua/dy/src/json/../mysql-connector/lib/libmysqlclient.a /home/meihua/dy/src/json/../thrift/lib/libthriftnb.a /home/meihua/dy/src/json/../thrift/lib/libthriftz.a /home/meihua/dy/src/json/../thrift/lib/libthrift.a /home/meihua/dy/src/json/../common_lib/output/lib/libcommon_lib.a -Xlinker "-)"


#---------- phony ----------
.PHONY:all
all:prepare \
demo \


.PHONY:prepare
prepare:
	mkdir -p ./output/bin

.PHONY:clean
clean:
	rm -rf /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_map.o ./output


#---------- link ----------
demo:/home/meihua/dy/src/json/impl/json_array.o \
/home/meihua/dy/src/json/demo/demo.o \
/home/meihua/dy/src/json/impl/json_string.o \
/home/meihua/dy/src/json/json.o \
/home/meihua/dy/src/json/impl/json_number.o \
/home/meihua/dy/src/json/impl/json_map.o \

	$(CXX) /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_map.o $(LIBPATH) -o ./output/bin/demo



#---------- obj ----------
/home/meihua/dy/src/json/impl/json_array.o: /home/meihua/dy/src/json/impl/json_array.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_array.o /home/meihua/dy/src/json/impl/json_array.cpp
/home/meihua/dy/src/json/demo/demo.o: /home/meihua/dy/src/json/demo/demo.cpp \
 /home/meihua/dy/src/json/demo/../json.h \
 /home/meihua/dy/src/json/demo/../json_obj.h \
 /home/meihua/dy/src/json/demo/../define.h \
 /home/meihua/dy/src/json/demo/../exception.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/demo/demo.o /home/meihua/dy/src/json/demo/demo.cpp
/home/meihua/dy/src/json/impl/json_string.o: /home/meihua/dy/src/json/impl/json_string.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_string.o /home/meihua/dy/src/json/impl/json_string.cpp
/home/meihua/dy/src/json/json.o: /home/meihua/dy/src/json/json.cpp /home/meihua/dy/src/json/json.h \
 /home/meihua/dy/src/json/json_obj.h /home/meihua/dy/src/json/define.h \
 /home/meihua/dy/src/json/exception.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/json.o /home/meihua/dy/src/json/json.cpp
/home/meihua/dy/src/json/impl/json_number.o: /home/meihua/dy/src/json/impl/json_number.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_number.o /home/meihua/dy/src/json/impl/json_number.cpp
/home/meihua/dy/src/json/impl/json_map.o: /home/meihua/dy/src/json/impl/json_map.cpp \
 /home/meihua/dy/src/json/impl/../json_obj.h \
 /home/meihua/dy/src/json/impl/../define.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/json/impl/json_map.o /home/meihua/dy/src/json/impl/json_map.cpp


