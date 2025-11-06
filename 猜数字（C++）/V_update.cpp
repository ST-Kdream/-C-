#include "V_update.h"

size_t WriteCallback(void* contents, size_t size, size_t numemb, std::string* s)
{
	if (s == nullptr)
		return 0;
	const size_t max_accept = 100;
	size_t length = size * numemb;
	if (s->size() + length > max_accept)
	{
		length = max_accept - s->size();
		if (length <= 0) 
			return 0;
	}
	try
	{
		s->append((char*)contents, length);
	}
	catch (std::bad_alloc& e)
	{
		return 0;
	}
	return length;
}

std::string get_remote_version()
{
	CURL* curl = curl_easy_init();
	std::string respond;
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, Remote_Version_URL);
		curl_easy_setopt(curl, CURLOPT_USERAGENT,
			"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36");
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L);      
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respond);

		CURLcode res = curl_easy_perform(curl);
		
		if (res != CURLE_OK)
		{
			std::cerr << "网络连接失败，请检查网络设置！" << std::endl;
			std::cerr << "错误码：" << curl_easy_strerror(res) << std::endl;
			respond = "";
		}
	}
	curl_easy_cleanup(curl);

	if (!respond.empty() && respond.back() == '\n')
	{
		respond.pop_back();
	}
	return respond;
}

bool is_update(const std::string& local_version, const std::string& remote_version)
{
	bool answer;
	auto split_version = [](const std::string& version)->std::vector<size_t>
		{
			std::vector<size_t> version_part;
			std::stringstream ss(version);
			std::string temp_part;

			while (getline(ss, temp_part, '.') && version_part.size() < 3)
			{
				try
				{
					version_part.push_back(stoi(temp_part));
				}
				catch (...)
				{
					return {};
				}
			}
			if (version_part.size() != 3)
				return {};
			return version_part;
		};
	auto local_part = split_version(local_version);
	auto remote_part = split_version(remote_version);

	for (int i = 0; i <= 2; i++)
	{
		if (local_part[i] == remote_part[i])
			answer = true;
		else
		{
			answer = false;
			break;
		}
	}
	return answer;
}

void version_check()
{
	std::cout << "游戏启动，正在检查更新，请稍后......" << std::endl;
	std::string remote_version = get_remote_version();
	if (remote_version.empty())
	{
		std::cout << "检查更新失败！" << std::endl;
		return;
	}
	if (is_update(Local_Version, remote_version))
		std::cout << "已是最新版本：" << Local_Version << std::endl;
	else
	{
		std::cout << "有新版本发布！" << std::endl;
		std::cout << "当前版本：" << Local_Version << '\t' << "最新版本：" << remote_version << std::endl;
		std::cout << "请前往 " << New_Download_URL << " 下载新版本" << std::endl;
	}
	std::cout << "________________________________________________________________________";

}

