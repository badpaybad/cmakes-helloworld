#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.
#https://hub.docker.com/_/microsoft-dotnet-sdk

#FROM mcr.microsoft.com/dotnet/sdk:3.1 AS base
FROM mcr.microsoft.com/dotnet/aspnet:3.1 AS base
RUN apt-get update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
RUN apt-get update -y
#RUN apt-get install htop -y
RUN apt-get install ffmpeg -y
WORKDIR /app
EXPOSE 80
#EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:3.1 AS build
WORKDIR /src
COPY ["Mnvn.WebAppDockerTest.csproj", "Mnvn.WebAppDockerTest/"]
#%appdata%\NuGet\NuGet.Config
#RUN dotnet restore "Mnvn.WebAppDockerTest/Mnvn.WebAppDockerTest.csproj"
#%appdata%\NuGet\NuGet.Config
COPY . ./Mnvn.WebAppDockerTest/

WORKDIR "/src/Mnvn.WebAppDockerTest"

#RUN dotnet nuget add source %FEED_SOURCE% -n PrivateFeed -u docker -p %FEED_ACCESSTOKEN% --store-password-in-clear-text --configfile nuget.config
#RUN dotnet nuget add source http://118.70.117.208:8123/nuget -n omt1 -u user -p 123@123 --store-password-in-clear-text --configfile nuget.config
#RUN dotnet build "Mnvn.WebAppDockerTest/Mnvn.WebAppDockerTest.csproj" -c Release -o /app/build
#https://docs.microsoft.com/en-us/nuget/consume-packages/configuring-nuget-behavior
RUN dotnet restore --configfile  "npm.config"
RUN dotnet build

FROM build AS publish
#RUN dotnet publish "Mnvn.WebAppDockerTest/Mnvn.WebAppDockerTest.csproj" -c Release -o /app/publish
RUN dotnet publish -c Release -o /app/publish

#COPY ././Mnvn.Core/bin/Debug/netcoreapp3.1/. ./app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Mnvn.WebAppDockerTest.dll"]

#docker build -t mnvntest .
#docker run -it --rm -p 5000:80 --name mnvntest_5000 mnvntest