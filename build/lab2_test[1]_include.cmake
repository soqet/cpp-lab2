if(EXISTS "C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/lab2_test[1]_tests.cmake")
  include("C:/Users/soqet/Documents/coding/nsu/course2/oop/lab2/build/lab2_test[1]_tests.cmake")
else()
  add_test(lab2_test_NOT_BUILT lab2_test_NOT_BUILT)
endif()
