echo Capturing current environment in "/home/lize/conan/hellopkg/test_package/build/generators/deactivate_conanbuildenv-release-x86_64.sh"
echo "echo Restoring environment" >> "/home/lize/conan/hellopkg/test_package/build/generators/deactivate_conanbuildenv-release-x86_64.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/lize/conan/hellopkg/test_package/build/generators/deactivate_conanbuildenv-release-x86_64.sh"
    else
        echo unset $v >> "/home/lize/conan/hellopkg/test_package/build/generators/deactivate_conanbuildenv-release-x86_64.sh"
    fi
done

echo Configuring environment variables
