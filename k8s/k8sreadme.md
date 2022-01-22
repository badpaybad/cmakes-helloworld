https://github.com/kubernetes/dashboard

https://github.com/kubernetes/dashboard/blob/master/docs/user/access-control/creating-sample-user.md



kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.3.1/aio/deploy/recommended.yaml

kubectl create sa admin-user -n kubernetes-dashboard

kubectl apply -f "C:\work\mnvn-dotnet-timeline\Mnvn.WebAppDockerTest\kuber\recommended.yaml"


kubectl apply -f "C:\work\mnvn-dotnet-timeline\Mnvn.WebAppDockerTest\kuber\dashboard-adminuser.yaml"


kubectl -n kubernetes-dashboard get secret $(kubectl -n kubernetes-dashboard get sa/admin-user -o jsonpath="{.secrets[0].name}") -o go-template="{{.data.token | base64decode}}"


kubectl -n kubernetes-dashboard get secret

kubectl -n kubernetes-dashboard get sa/admin-user -o jsonpath="{.secrets[0].name}" -o go-template="{{.data.token | base64decode }}"

kubectl proxy
http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/#/login

https://andrewlock.net/running-kubernetes-and-the-dashboard-with-docker-desktop/


https://faun.pub/how-to-deploy-a-net-5-api-in-a-kubernetes-cluster-53212af6a0e2

 
 // kubectl apply -f .\mnvntest.deploy.yaml
 kubectl create -f .\mnvntest.deploy.yaml
 kubectl get pods -o wide
 kubectl delete deployment mnvntest-deploy

 kubectl apply -f mnvntest.service.yaml
 kubectl get service -o wide
 kubectl delete services mnvntest-service