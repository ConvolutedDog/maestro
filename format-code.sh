# This bash script formats code using clang-format

THIS_DIR="$( cd "$( dirname "$BASH_SOURCE" )" && pwd )"

clang-format -i ${THIS_DIR}/maestro-top.cpp

clang-format -i ${THIS_DIR}/cost-model/include/*.h
clang-format -i ${THIS_DIR}/cost-model/include/*.hpp

clang-format -i ${THIS_DIR}/cost-model/include/user-api/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/tools/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/design-space-exploration/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/dataflow-specification-language/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/dataflow-analysis/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/cost-analysis/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/base/*.hpp
clang-format -i ${THIS_DIR}/cost-model/include/abstract-hardware-model/*.hpp

clang-format -i ${THIS_DIR}/cost-model/src/*.cpp
