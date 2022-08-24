echo Capturing current environment in "/home/lize/conan/hellopkg2/test_package/build/generators/deactivate_conanrunenv-release-x86_64.sh"
echo "echo Restoring environment" >> "/home/lize/conan/hellopkg2/test_package/build/generators/deactivate_conanrunenv-release-x86_64.sh"
for v in LD_LIBRARY_PATH DYLD_LIBRARY_PATH
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/lize/conan/hellopkg2/test_package/build/generators/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "/home/lize/conan/hellopkg2/test_package/build/generators/deactivate_conanrunenv-release-x86_64.sh"
    fi
done

echo Configuring environment variables

export LD_LIBRARY_PATH="/home/lize/.conan/data/hello/0.2/demo/lize/package/b911f48570f9bb2902d9e83b2b9ebf9d376c8c56/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="/home/lize/.conan/data/hello/0.2/demo/lize/package/b911f48570f9bb2902d9e83b2b9ebf9d376c8c56/lib:$DYLD_LIBRARY_PATH"