pipeline {
    triggers { pollSCM('H */4 * * *') }
    agent {
        dockerfile {
            filename 'Dockerfile'
            dir '.'
            args '-v /var/run/docker.sock:/var/run/docker.sock -v /root/:/root/ --user root --net="host"'
        }
    }
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh './build_scripts/makeC.sh'
                sh './build_scripts/makedemo.sh'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                ctest arguments: '''
                --test-dir build/Release/test/
                --output-junit ctest.junit.xml
                ''', installation: 'InSearchPath'
                sh 'pylint --output-format=junit WebappDemo/src/ > build/Release/test/pylint.junit.xml || true'
                sh 'pytest --junit-xml=build/Release/test/pytest.junit.xml || true'
            }
        }
        stage('Docu') {
            steps {
                echo 'Building Documentation...'
                sh './build_scripts/makedoc.sh'
            }
        }
        stage('Deploy') {
            when {
                expression {
                    env.BRANCH_NAME == 'main'
                }
            }
            steps {
                echo 'Deploying....'
                sh './build_scripts/deploy.sh'
            }
        }
    }
    post {
        always {
            // Postprocess test results
            junit 'build/Release/test/ctest.junit.xml'
            junit 'build/Release/test/pylint.junit.xml'
            junit 'build/Release/test/pytest.junit.xml'
            // Archive generated documentation
            archiveArtifacts artifacts: 'build/docu/**/*.pdf', onlyIfSuccessful: true
        }
    }
}
